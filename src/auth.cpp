#include "auth.h"
#include "logger.h"
#include "utils.h"
#include <cstdio>
#include <cstring>

AuthManager::AuthManager() {
    hasPassword = false;
    strcpy(username, "admin");
    passwordHash[0] = '\0';
}

bool AuthManager::isFirstRun() {
    FILE* fp = fopen(FILE_PASSWORD, "rb");
    if (fp == NULL) {
        return true;
    }
    fclose(fp);
    return false;
}

bool AuthManager::loadPassword() {
    FILE* fp = fopen(FILE_PASSWORD, "rb");
    if (fp == NULL) {
        return false;
    }
    if (fread(username, sizeof(char), 64, fp) != 64) {
        fclose(fp);
        return false;
    }
    if (fread(passwordHash, sizeof(char), 64, fp) != 64) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    hasPassword = true;
    return true;
}

bool AuthManager::savePassword() {
    FILE* fp = fopen(FILE_PASSWORD, "wb");
    if (fp == NULL) {
        return false;
    }
    if (fwrite(username, sizeof(char), 64, fp) != 64) {
        fclose(fp);
        return false;
    }
    if (fwrite(passwordHash, sizeof(char), 64, fp) != 64) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    return true;
}

void AuthManager::encryptPassword(const char* plain, char* hash) {
    int len = strlen(plain);
    for (int i = 0; i < 64; i++) {
        if (i < len) {
            hash[i] = plain[i] ^ 0x5A;
        } else {
            hash[i] = '\0';
        }
    }
}

void AuthManager::decryptPassword(const char* hash, char* plain) {
    for (int i = 0; i < 64; i++) {
        if (hash[i] != '\0') {
            plain[i] = hash[i] ^ 0x5A;
        } else {
            plain[i] = '\0';
            break;
        }
    }
}

bool AuthManager::verifyPassword(const char* inputPassword) {
    if (!hasPassword && passwordHash[0] == '\0') {
        return false;
    }
    char encrypted[64];
    encryptPassword(inputPassword, encrypted);
    for (int i = 0; i < 64; i++) {
        if (encrypted[i] != passwordHash[i]) {
            return false;
        }
        if (encrypted[i] == '\0' && passwordHash[i] == '\0') {
            break;
        }
    }
    return true;
}

bool AuthManager::setPassword(const char* oldPassword, const char* newPassword) {
    if (!verifyPassword(oldPassword)) {
        return false;
    }
    int len = strlen(newPassword);
    if (len < PASSWORD_MIN_LEN || len > PASSWORD_MAX_LEN) {
        return false;
    }
    encryptPassword(newPassword, passwordHash);
    hasPassword = true;
    return savePassword();
}

bool AuthManager::setInitialPassword(const char* newPassword) {
    int len = strlen(newPassword);
    if (len < PASSWORD_MIN_LEN || len > PASSWORD_MAX_LEN) {
        printf("密码长度必须在 %d 到 %d 个字符之间\n", PASSWORD_MIN_LEN, PASSWORD_MAX_LEN);
        return false;
    }
    encryptPassword(newPassword, passwordHash);
    hasPassword = true;
    return savePassword();
}

bool AuthManager::login() {
    if (isFirstRun()) {
        printf("首次使用，请设置管理员密码\n");
        char newPwd[64];
        while (1) {
            getStringInput("请输入新密码 (6-16位): ", newPwd, 64);
            if (setInitialPassword(newPwd)) {
                printf("密码设置成功\n");
                Logger::logLogin(true);
                return true;
            }
        }
    }

    if (!hasPassword && passwordHash[0] == '\0') {
        loadPassword();
    }

    for (int attempt = 1; attempt <= 3; attempt++) {
        char inputPwd[64];
        printf("请输入管理员密码 (第 %d/3 次): ", attempt);
        getStringInput("", inputPwd, 64);

        if (verifyPassword(inputPwd)) {
            printf("登录成功\n");
            Logger::logLogin(true);
            return true;
        }

        printf("密码错误\n");
        Logger::logLogin(false);
    }

    printf("密码错误次数过多，程序退出\n");
    return false;
}
