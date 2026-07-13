/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 日志模块实现，提供操作日志的记录与查看功能
 */

#include "logger.h"
#include "utils.h"
#include <cstdio>

/*
 * 函数作用: 向日志文件追加一条操作日志记录
 * 入参: operation - 操作描述字符串
 * 返回值: 无
 * 异常提示: 无
 */
void Logger::logOperation(const char* operation) {
    FILE* fp = fopen(FILE_LOG, "a");
    if (fp == NULL) {
        return;
    }
    char timestamp[32];
    getCurrentDateTime(timestamp);
    fprintf(fp, "%s [操作] %s\n", timestamp, operation);
    fclose(fp);
}

/*
 * 函数作用: 记录添加实体操作日志
 * 入参: entity - 实体类型名称, id - 实体ID
 * 返回值: 无
 * 异常提示: 无
 */
void Logger::logAdd(const char* entity, int id) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "添加%s ID:%d", entity, id);
    logOperation(msg);
}

/*
 * 函数作用: 记录删除实体操作日志
 * 入参: entity - 实体类型名称, id - 实体ID
 * 返回值: 无
 * 异常提示: 无
 */
void Logger::logDelete(const char* entity, int id) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "删除%s ID:%d", entity, id);
    logOperation(msg);
}

/*
 * 函数作用: 记录修改实体操作日志
 * 入参: entity - 实体类型名称, id - 实体ID
 * 返回值: 无
 * 异常提示: 无
 */
void Logger::logModify(const char* entity, int id) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "修改%s ID:%d", entity, id);
    logOperation(msg);
}

/*
 * 函数作用: 记录租车操作日志
 * 入参: rentId - 租车记录ID, vehicleId - 车辆ID, renterId - 租车人ID
 * 返回值: 无
 * 异常提示: 无
 */
void Logger::logRent(int rentId, int vehicleId, int renterId) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "租车: 租车ID=%d 车辆ID=%d 用户ID=%d", rentId, vehicleId, renterId);
    logOperation(msg);
}

/*
 * 函数作用: 记录退车操作日志
 * 入参: rentId - 租车记录ID, vehicleId - 车辆ID, renterId - 租车人ID, fee - 费用
 * 返回值: 无
 * 异常提示: 无
 */
void Logger::logReturn(int rentId, int vehicleId, int renterId, double fee) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "退车: 租车ID=%d 车辆ID=%d 用户ID=%d 费用=%.2f", rentId, vehicleId, renterId, fee);
    logOperation(msg);
}

/*
 * 函数作用: 记录登录操作日志（成功或失败）
 * 入参: success - true 表示登录成功，false 表示登录失败
 * 返回值: 无
 * 异常提示: 无
 */
void Logger::logLogin(bool success) {
    logOperation(success ? "登录成功" : "登录失败");
}

/*
 * 函数作用: 读取并显示所有操作日志
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void Logger::showLog() {
    FILE* fp = fopen(FILE_LOG, "r");
    if (fp == NULL) {
        printf("暂无操作日志\n");
        return;
    }
    char line[512];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);
}
