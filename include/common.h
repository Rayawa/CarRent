#ifndef COMMON_H
#define COMMON_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 定义系统全局常量、枚举类型和公共头文件引用，为所有模块提供基础定义
 */

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int MAX_NAME_LEN = 32;
const int MAX_BRAND_LEN = 32;
const int MAX_TYPE_LEN = 32;
const int MAX_COLOR_LEN = 16;
const int MAX_PLATE_LEN = 16;
const int MAX_PHONE_LEN = 20;
const int MAX_IDCARD_LEN = 20;
const int MAX_LICENSE_LEN = 20;
const int MAX_INSURANCE_LEN = 64;
const int MAX_DATE_LEN = 16;
const int MAX_ADDR_LEN = 64;
const int MAX_LOG_LEN = 256;

const int MAX_VEHICLES = 1000;
const int MAX_RENTERS = 1000;
const int MAX_RENTS = 5000;

const int PASSWORD_MIN_LEN = 6;
const int PASSWORD_MAX_LEN = 16;

const char FILE_VEHICLE[] = "vehicle.dat";
const char FILE_RENTER[] = "renter.dat";
const char FILE_RENT[] = "rent.dat";
const char FILE_PASSWORD[] = "pwd.dat";
const char FILE_LOG[] = "log.txt";

enum VehicleStatus {
    STATUS_AVAILABLE = 0,
    STATUS_RENTED = 1,
    STATUS_MAINTENANCE = 2
};

enum RentStatus {
    RENT_ACTIVE = 0,
    RENT_RETURNED = 1
};

#endif
