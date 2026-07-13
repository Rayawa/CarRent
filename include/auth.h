#ifndef AUTH_H
#define AUTH_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供登录认证和密码管理功能，包括密码加密、验证和修改
 */

#include "common.h"

class AuthManager {
private:
    char username[64];
    char passwordHash[64];
    bool hasPassword;

    /*
     * 函数作用: 将明文密码加密为哈希值存储
     * 入参: plain - 明文密码；hash - 存储哈希结果的缓冲区
     * 返回值: 无
     * 异常提示: 无
     */
    void encryptPassword(const char* plain, char* hash);

    /*
     * 函数作用: 将存储的哈希值解密为明文密码
     * 入参: hash - 加密后的哈希值；plain - 存储解密结果的缓冲区
     * 返回值: 无
     * 异常提示: 无
     */
    void decryptPassword(const char* hash, char* plain);

public:
    /*
     * 函数作用: 构造认证管理器，检查是否为首次运行
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    AuthManager();

    /*
     * 函数作用: 判断当前是否为首次运行（未设置密码）
     * 入参: 无
     * 返回值: 首次运行返回true，否则返回false
     * 异常提示: 无
     */
    bool isFirstRun();

    /*
     * 函数作用: 从文件加载密码哈希值
     * 入参: 无
     * 返回值: 加载成功返回true，失败返回false
     * 异常提示: 无
     */
    bool loadPassword();

    /*
     * 函数作用: 将密码哈希值保存到文件
     * 入参: 无
     * 返回值: 保存成功返回true，失败返回false
     * 异常提示: 无
     */
    bool savePassword();

    /*
     * 函数作用: 验证输入的密码是否正确
     * 入参: inputPassword - 用户输入的密码
     * 返回值: 密码正确返回true，否则返回false
     * 异常提示: 无
     */
    bool verifyPassword(const char* inputPassword);

    /*
     * 函数作用: 修改密码（需提供旧密码验证）
     * 入参: oldPassword - 旧密码；newPassword - 新密码
     * 返回值: 修改成功返回true，失败返回false
     * 异常提示: 无
     */
    bool setPassword(const char* oldPassword, const char* newPassword);

    /*
     * 函数作用: 首次运行时设置初始密码
     * 入参: newPassword - 新密码
     * 返回值: 设置成功返回true，失败返回false
     * 异常提示: 无
     */
    bool setInitialPassword(const char* newPassword);

    /*
     * 函数作用: 执行用户登录流程，最多允许3次尝试
     * 入参: 无
     * 返回值: 登录成功返回true，失败返回false
     * 异常提示: 无
     */
    bool login();
};

#endif
