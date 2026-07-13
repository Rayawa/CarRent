#ifndef RENT_RECORD_H
#define RENT_RECORD_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 定义租赁记录数据结构及租赁记录相关的工具函数声明
 */

#include "common.h"

struct RentRecord {
    int id;
    int vehicleId;
    int renterId;
    char rentDate[MAX_DATE_LEN];
    char expectedReturnDate[MAX_DATE_LEN];
    char actualReturnDate[MAX_DATE_LEN];
    double deposit;
    double dailyRate;
    double totalFee;
    int status;
    char vehicleBrand[MAX_BRAND_LEN];
    char vehiclePlate[MAX_PLATE_LEN];
    char renterName[MAX_NAME_LEN];
    char renterLicense[MAX_LICENSE_LEN];
};

/*
 * 函数作用: 初始化租赁记录结构体，将各字段置为默认值
 * 入参: r - 指向待初始化租赁记录结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void initRentRecord(RentRecord* r);

/*
 * 函数作用: 打印单条租赁记录的详细信息
 * 入参: r - 指向租赁记录结构体的常量指针
 * 返回值: 无
 * 异常提示: 无
 */
void rentRecordPrint(const RentRecord* r);

/*
 * 函数作用: 打印租赁记录列表的表头行
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void rentRecordPrintHeader();

/*
 * 函数作用: 打印租赁记录列表的一行数据
 * 入参: r - 指向租赁记录结构体的常量指针
 * 返回值: 无
 * 异常提示: 无
 */
void rentRecordPrintRow(const RentRecord* r);

/*
 * 函数作用: 将租赁状态枚举值转换为对应的中文字符串
 * 入参: status - 租赁状态枚举值
 * 返回值: 租赁状态的中文字符串
 * 异常提示: 无
 */
const char* rentStatusStr(int status);

#endif
