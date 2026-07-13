#ifndef UI_H
#define UI_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供系统的命令行交互界面，管理所有菜单导航和用户操作入口
 */

#include "common.h"
#include "vehicle_manager.h"
#include "renter_manager.h"
#include "rent_manager.h"
#include "auth.h"

class UI {
private:
    VehicleManager vehicleManager;
    RenterManager renterManager;
    RentManager rentManager;
    AuthManager authManager;
    bool running;

    /*
     * 函数作用: 显示主菜单并处理导航选择
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void mainMenu();

    /*
     * 函数作用: 显示车辆管理子菜单并处理导航选择
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void vehicleMenu();

    /*
     * 函数作用: 显示租车人管理子菜单并处理导航选择
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void renterMenu();

    /*
     * 函数作用: 显示租车操作子菜单并处理导航选择
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void rentMenu();

    /*
     * 函数作用: 显示还车操作子菜单并处理导航选择
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void returnMenu();

    /*
     * 函数作用: 显示查询子菜单并处理导航选择
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void queryMenu();

    /*
     * 函数作用: 显示统计子菜单并处理导航选择
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void statisticsMenu();

    /*
     * 函数作用: 显示系统管理子菜单并处理导航选择
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void systemMenu();

    /*
     * 函数作用: 显示扩展功能子菜单并处理导航选择
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void extendedMenu();

    /*
     * 函数作用: 处理添加车辆的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleAddVehicle();

    /*
     * 函数作用: 处理删除车辆的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleDeleteVehicle();

    /*
     * 函数作用: 处理修改车辆信息的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleModifyVehicle();

    /*
     * 函数作用: 处理列出所有车辆的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleListVehicles();

    /*
     * 函数作用: 处理添加租车人的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleAddRenter();

    /*
     * 函数作用: 处理删除租车人的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleDeleteRenter();

    /*
     * 函数作用: 处理修改租车人信息的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleModifyRenter();

    /*
     * 函数作用: 处理列出所有租车人的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleListRenters();

    /*
     * 函数作用: 处理租车操作业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleRentVehicle();

    /*
     * 函数作用: 处理还车操作业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleReturnVehicle();

    /*
     * 函数作用: 处理打印小票的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handlePrintReceipt();

    /*
     * 函数作用: 处理列出所有租赁记录的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleListRentRecords();

    /*
     * 函数作用: 处理查询车辆的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleQueryVehicles();

    /*
     * 函数作用: 处理查询租车人的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleQueryRenters();

    /*
     * 函数作用: 处理查询租赁记录的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleQueryRentRecords();

    /*
     * 函数作用: 处理车辆统计的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleVehicleStatistics();

    /*
     * 函数作用: 处理租车人统计的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleRenterStatistics();

    /*
     * 函数作用: 处理租赁统计的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleRentStatistics();

    /*
     * 函数作用: 处理修改密码的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleChangePassword();

    /*
     * 函数作用: 处理导出报表的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleExportReport();

    /*
     * 函数作用: 处理查看操作日志的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleViewLog();

    /*
     * 函数作用: 处理清空数据的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleClearData();

    /*
     * 函数作用: 处理模糊搜索的业务流程
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void handleFuzzySearch();

    /*
     * 函数作用: 显示系统Banner横幅
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void showBanner();

    /*
     * 函数作用: 通过车辆编号自动补全输入
     * 入参: buffer - 存储输入结果的缓冲区；bufferSize - 缓冲区大小
     * 返回值: 无
     * 异常提示: 无
     */
    void handleAutoCompleteVehicleId(char* buffer, int bufferSize);

    /*
     * 函数作用: 检查车辆是否已存在（按车牌号）
     * 入参: plateNo - 待检查的车牌号
     * 返回值: 存在重复返回1，否则返回0
     * 异常提示: 无
     */
    int checkDuplicateVehicleByPlate(const char* plateNo);

    /*
     * 函数作用: 检查租车人是否已存在（按驾照号）
     * 入参: licenseNo - 待检查的驾照号
     * 返回值: 存在重复返回1，否则返回0
     * 异常提示: 无
     */
    int checkDuplicateRenterByLicense(const char* licenseNo);

    /*
     * 函数作用: 显示车辆情况动态状态图
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void showVehicleDynamicDisplay();

    /*
     * 函数作用: 显示统计对比柱状图
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void showComparisonBarChart();

    /*
     * 函数作用: 分页显示记录列表
     * 入参: records - 待显示的记录链表
     * 返回值: 无
     * 异常提示: 无
     */
    void handlePaginatedRentRecords();

public:
    /*
     * 函数作用: 构造UI界面对象，初始化各管理器
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    UI();

    /*
     * 函数作用: 启动程序主循环，进入主菜单
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void run();
};

#endif
