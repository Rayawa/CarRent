#ifndef AUTH_H
#define AUTH_H

#include "common.h"

class AuthManager {
private:
    char username[64];
    char passwordHash[64];
    bool hasPassword;

    void encryptPassword(const char* plain, char* hash);
    void decryptPassword(const char* hash, char* plain);

public:
    AuthManager();
    bool isFirstRun();
    bool loadPassword();
    bool savePassword();
    bool verifyPassword(const char* inputPassword);
    bool setPassword(const char* oldPassword, const char* newPassword);
    bool setInitialPassword(const char* newPassword);
    bool login();
};

#endif
