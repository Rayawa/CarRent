#ifndef STATISTICS_H
#define STATISTICS_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供数据统计和图表展示功能，包括仪表盘、柱状图和趋势图
 */

#include "common.h"

class VehicleManager;
class RenterManager;
class RentManager;

class Statistics {
public:
    /*
     * 函数作用: 显示系统综合仪表盘，汇总车辆、租车人和租赁数据
     * 入参: vm - 车辆管理器指针；rm - 租车人管理器指针；rentm - 租赁管理器指针
     * 返回值: 无
     * 异常提示: 无
     */
    static void showDashboard(VehicleManager* vm, RenterManager* rm, RentManager* rentm);

    /*
     * 函数作用: 显示车辆统计柱状图
     * 入参: vm - 车辆管理器指针
     * 返回值: 无
     * 异常提示: 无
     */
    static void showVehicleBarChart(VehicleManager* vm);

    /*
     * 函数作用: 显示租赁趋势图
     * 入参: rentm - 租赁管理器指针
     * 返回值: 无
     * 异常提示: 无
     */
    static void showRentTrendChart(RentManager* rentm);

    /*
     * 函数作用: 显示租赁类型分布柱状图
     * 入参: rentm - 租赁管理器指针
     * 返回值: 无
     * 异常提示: 无
     */
    static void showRentTypeBarChart(RentManager* rentm);

    /*
     * 函数作用: 显示营收图表
     * 入参: rentm - 租赁管理器指针
     * 返回值: 无
     * 异常提示: 无
     */
    static void showRevenueChart(RentManager* rentm);
};

#endif
