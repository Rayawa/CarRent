#ifndef LOGGER_H
#define LOGGER_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供操作日志记录功能，将系统关键操作写入日志文件
 */

#include "common.h"

class Logger {
public:
    /*
     * 函数作用: 记录一条通用操作日志
     * 入参: operation - 操作描述字符串
     * 返回值: 无
     * 异常提示: 无
     */
    static void logOperation(const char* operation);

    /*
     * 函数作用: 记录新增实体操作日志
     * 入参: entity - 实体类型名称；id - 实体编号
     * 返回值: 无
     * 异常提示: 无
     */
    static void logAdd(const char* entity, int id);

    /*
     * 函数作用: 记录删除实体操作日志
     * 入参: entity - 实体类型名称；id - 实体编号
     * 返回值: 无
     * 异常提示: 无
     */
    static void logDelete(const char* entity, int id);

    /*
     * 函数作用: 记录修改实体操作日志
     * 入参: entity - 实体类型名称；id - 实体编号
     * 返回值: 无
     * 异常提示: 无
     */
    static void logModify(const char* entity, int id);

    /*
     * 函数作用: 记录租车操作日志
     * 入参: rentId - 租赁编号；vehicleId - 车辆编号；renterId - 租车人编号
     * 返回值: 无
     * 异常提示: 无
     */
    static void logRent(int rentId, int vehicleId, int renterId);

    /*
     * 函数作用: 记录还车操作日志
     * 入参: rentId - 租赁编号；vehicleId - 车辆编号；renterId - 租车人编号；fee - 租赁费用
     * 返回值: 无
     * 异常提示: 无
     */
    static void logReturn(int rentId, int vehicleId, int renterId, double fee);

    /*
     * 函数作用: 记录登录操作日志
     * 入参: success - 登录成功为true，失败为false
     * 返回值: 无
     * 异常提示: 无
     */
    static void logLogin(bool success);

    /*
     * 函数作用: 显示日志文件内容
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    static void showLog();
};

#endif
