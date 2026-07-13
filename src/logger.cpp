#include "logger.h"
#include "utils.h"
#include <cstdio>

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

void Logger::logAdd(const char* entity, int id) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "添加%s ID:%d", entity, id);
    logOperation(msg);
}

void Logger::logDelete(const char* entity, int id) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "删除%s ID:%d", entity, id);
    logOperation(msg);
}

void Logger::logModify(const char* entity, int id) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "修改%s ID:%d", entity, id);
    logOperation(msg);
}

void Logger::logRent(int rentId, int vehicleId, int renterId) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "租车: 租车ID=%d 车辆ID=%d 用户ID=%d", rentId, vehicleId, renterId);
    logOperation(msg);
}

void Logger::logReturn(int rentId, int vehicleId, int renterId, double fee) {
    char msg[MAX_LOG_LEN];
    snprintf(msg, MAX_LOG_LEN, "退车: 租车ID=%d 车辆ID=%d 用户ID=%d 费用=%.2f", rentId, vehicleId, renterId, fee);
    logOperation(msg);
}

void Logger::logLogin(bool success) {
    logOperation(success ? "登录成功" : "登录失败");
}

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
