#ifndef VEHICLE_MANAGER_H
#define VEHICLE_MANAGER_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供车辆管理功能，包括车辆的增删改查、文件读写和统计查询
 */

#include "common.h"
#include "vehicle.h"
#include "linked_list.h"

class VehicleManager {
private:
    LinkedList<Vehicle> vehicles;
    int nextId;

    /*
     * 函数作用: 按编号查找车辆在链表中的索引
     * 入参: id - 车辆编号
     * 返回值: 找到返回索引值，未找到返回-1
     * 异常提示: 无
     */
    int findVehicleIndexById(int id);

    /*
     * 函数作用: 更新下一个可用编号为当前最大编号加1
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void updateNextId();

public:
    /*
     * 函数作用: 构造车辆管理器，初始化链表和编号
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    VehicleManager();

    /*
     * 函数作用: 从文件加载车辆数据到内存链表
     * 入参: 无
     * 返回值: 加载成功返回true，失败返回false
     * 异常提示: 无
     */
    bool loadFromFile();

    /*
     * 函数作用: 将内存链表中的车辆数据保存到文件
     * 入参: 无
     * 返回值: 保存成功返回true，失败返回false
     * 异常提示: 无
     */
    bool saveToFile();

    /*
     * 函数作用: 添加一辆新车到系统中
     * 入参: v - 待添加的车辆结构体引用
     * 返回值: 添加成功返回true，失败返回false
     * 异常提示: 无
     */
    bool addVehicle(const Vehicle& v);

    /*
     * 函数作用: 按编号删除指定车辆
     * 入参: id - 待删除的车辆编号
     * 返回值: 删除成功返回true，失败返回false
     * 异常提示: 无
     */
    bool deleteVehicle(int id);

    /*
     * 函数作用: 按编号修改指定车辆信息
     * 入参: id - 车辆编号；v - 包含新数据的车辆结构体引用
     * 返回值: 修改成功返回true，失败返回false
     * 异常提示: 无
     */
    bool modifyVehicle(int id, const Vehicle& v);

    /*
     * 函数作用: 按编号查找车辆
     * 入参: id - 车辆编号
     * 返回值: 找到返回车辆指针，未找到返回nullptr
     * 异常提示: 无
     */
    Vehicle* findVehicleById(int id);

    /*
     * 函数作用: 获取所有车辆的链表
     * 入参: 无
     * 返回值: 指向车辆链表的指针
     * 异常提示: 无
     */
    LinkedList<Vehicle>* getAllVehicles();

    /*
     * 函数作用: 按品牌查询车辆
     * 入参: brand - 品牌名称
     * 返回值: 匹配的车辆链表
     * 异常提示: 无
     */
    LinkedList<Vehicle> queryByBrand(const char* brand);

    /*
     * 函数作用: 按类型查询车辆
     * 入参: type - 车辆类型
     * 返回值: 匹配的车辆链表
     * 异常提示: 无
     */
    LinkedList<Vehicle> queryByType(const char* type);

    /*
     * 函数作用: 按颜色查询车辆
     * 入参: color - 颜色名称
     * 返回值: 匹配的车辆链表
     * 异常提示: 无
     */
    LinkedList<Vehicle> queryByColor(const char* color);

    /*
     * 函数作用: 按状态查询车辆
     * 入参: status - 车辆状态枚举值
     * 返回值: 匹配的车辆链表
     * 异常提示: 无
     */
    LinkedList<Vehicle> queryByStatus(int status);

    /*
     * 函数作用: 按关键词模糊查询车辆
     * 入参: keyword - 搜索关键词
     * 返回值: 匹配的车辆链表
     * 异常提示: 无
     */
    LinkedList<Vehicle> queryFuzzy(const char* keyword);

    /*
     * 函数作用: 统计某品牌车辆数量
     * 入参: brand - 品牌名称
     * 返回值: 该品牌车辆数量
     * 异常提示: 无
     */
    int countByBrand(const char* brand);

    /*
     * 函数作用: 统计某类型车辆数量
     * 入参: type - 车辆类型
     * 返回值: 该类型车辆数量
     * 异常提示: 无
     */
    int countByType(const char* type);

    /*
     * 函数作用: 统计某颜色车辆数量
     * 入参: color - 颜色名称
     * 返回值: 该颜色车辆数量
     * 异常提示: 无
     */
    int countByColor(const char* color);

    /*
     * 函数作用: 统计某状态车辆数量
     * 入参: status - 车辆状态枚举值
     * 返回值: 该状态车辆数量
     * 异常提示: 无
     */
    int countByStatus(int status);

    /*
     * 函数作用: 获取车辆总数
     * 入参: 无
     * 返回值: 系统中车辆总数量
     * 异常提示: 无
     */
    int getTotalCount();

    /*
     * 函数作用: 获取当前可租车辆数量
     * 入参: 无
     * 返回值: 可租车辆数量
     * 异常提示: 无
     */
    int getAvailableCount();

    /*
     * 函数作用: 获取当前已租车辆数量
     * 入参: 无
     * 返回值: 已租车辆数量
     * 异常提示: 无
     */
    int getRentedCount();

    /*
     * 函数作用: 估算所有车辆的总价值
     * 入参: 无
     * 返回值: 估算总价值
     * 异常提示: 无
     */
    double getTotalValue();

    /*
     * 函数作用: 打印车辆统计信息
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void printStatistics();
};

#endif
