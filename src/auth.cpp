/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 认证模块实现，提供管理员密码管理、登录验证、密码加密存储等功能
 */

#include "auth.h"
#include "logger.h"
#include "utils.h"
#include <cstdio>
#include <cstring>

/*
 * 函数作用: 构造函数，初始化 AuthManager 对象
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
AuthManager::AuthManager() {
    hasPassword = false;
    strcpy(username, "admin");
    passwordHash[0] = '\0';
}

/*
 * 函数作用: 判断程序是否为首次运行（密码文件不存在）
 * 入参: 无
 * 返回值: true 表示首次运行，false 表示已有密码文件
 * 异常提示: 无
 */
bool AuthManager::isFirstRun() {
    FILE* fp = fopen(FILE_PASSWORD, "rb");
    if (fp == NULL) {
        return true;
    }
    fclose(fp);
    return false;
}

/*
 * 函数作用: 从文件中加载用户名和密码哈希
 * 入参: 无
 * 返回值: true 表示加载成功，false 表示加载失败
 * 异常提示: 无
 */
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

/*
 * 函数作用: 将用户名和密码哈希保存到文件
 * 入参: 无
 * 返回值: true 表示保存成功，false 表示保存失败
 * 异常提示: 无
 */
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

/*
 * 函数作用: 使用 XOR 加密算法对明文密码进行加密
 * 入参: plain - 明文密码, hash - 存储加密结果的缓冲区（长度64）
 * 返回值: 无
 * 异常提示: 无
 */
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

/*
 * 函数作用: 使用 XOR 解密算法将密码哈希还原为明文密码
 * 入参: hash - 加密后的密码哈希, plain - 存储解密结果的缓冲区
 * 返回值: 无
 * 异常提示: 无
 */
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

/*
 * 函数作用: 验证用户输入的密码是否与存储的密码哈希匹配
 * 入参: inputPassword - 用户输入的明文密码
 * 返回值: true 表示密码正确，false 表示密码错误
 * 异常提示: 无
 */
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

/*
 * 函数作用: 修改管理员密码（需验证旧密码）
 * 入参: oldPassword - 旧密码, newPassword - 新密码
 * 返回值: true 表示修改成功，false 表示修改失败
 * 异常提示: 无
 */
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

/*
 * 函数作用: 首次使用时设置初始密码
 * 入参: newPassword - 新密码
 * 返回值: true 表示设置成功，false 表示设置失败
 * 异常提示: 无
 */
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

/*
 * 函数作用: 管理员登录流程，首次使用时引导设置密码，最多允许3次尝试
 * 入参: 无
 * 返回值: true 表示登录成功，false 表示登录失败（3次错误后退出）
 * 异常提示: 无
 */
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
