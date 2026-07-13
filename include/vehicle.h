#ifndef VEHICLE_H
#define VEHICLE_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 定义车辆数据结构及车辆相关的工具函数声明
 */

#include "common.h"

struct Vehicle {
    int id;
    char plateNo[MAX_PLATE_LEN];
    char brand[MAX_BRAND_LEN];
    char type[MAX_TYPE_LEN];
    char color[MAX_COLOR_LEN];
    char purchaseDate[MAX_DATE_LEN];
    int status;
    double dailyRate;
    double mileage;
    char insurance[MAX_INSURANCE_LEN];
};

/*
 * 函数作用: 初始化车辆结构体，将各字段置为默认值
 * 入参: v - 指向待初始化车辆结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void initVehicle(Vehicle* v);

/*
 * 函数作用: 打印单辆车辆的详细信息
 * 入参: v - 指向车辆结构体的常量指针
 * 返回值: 无
 * 异常提示: 无
 */
void vehiclePrint(const Vehicle* v);

/*
 * 函数作用: 打印车辆列表的表头行
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void vehiclePrintHeader();

/*
 * 函数作用: 打印车辆列表的一行数据
 * 入参: v - 指向车辆结构体的常量指针
 * 返回值: 无
 * 异常提示: 无
 */
void vehiclePrintRow(const Vehicle* v);

/*
 * 函数作用: 将车辆状态枚举值转换为对应的中文字符串
 * 入参: status - 车辆状态枚举值
 * 返回值: 车辆状态的中文字符串
 * 异常提示: 无
 */
const char* vehicleStatusStr(int status);

#endif
