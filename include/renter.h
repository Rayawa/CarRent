#ifndef RENTER_H
#define RENTER_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 定义租车人数据结构及租车人相关的工具函数声明
 */

#include "common.h"

struct Renter {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char gender;
    char phone[MAX_PHONE_LEN];
    char licenseNo[MAX_LICENSE_LEN];
    char idCard[MAX_IDCARD_LEN];
    int drivingYears;
    int rentCount;
};

/*
 * 函数作用: 初始化租车人结构体，将各字段置为默认值
 * 入参: r - 指向待初始化租车人结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void initRenter(Renter* r);

/*
 * 函数作用: 打印单个租车人的详细信息
 * 入参: r - 指向租车人结构体的常量指针
 * 返回值: 无
 * 异常提示: 无
 */
void renterPrint(const Renter* r);

/*
 * 函数作用: 打印租车人列表的表头行
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void renterPrintHeader();

/*
 * 函数作用: 打印租车人列表的一行数据
 * 入参: r - 指向租车人结构体的常量指针
 * 返回值: 无
 * 异常提示: 无
 */
void renterPrintRow(const Renter* r);

#endif
