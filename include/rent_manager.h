#ifndef RENT_MANAGER_H
#define RENT_MANAGER_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供租赁业务管理功能，包括租车、还车、租赁记录查询和统计
 */

#include "common.h"
#include "rent_record.h"
#include "linked_list.h"

class VehicleManager;
class RenterManager;

class RentManager {
private:
    LinkedList<RentRecord> rentRecords;
    int nextId;

    /*
     * 函数作用: 按编号查找租赁记录在链表中的索引
     * 入参: id - 租赁记录编号
     * 返回值: 找到返回索引值，未找到返回-1
     * 异常提示: 无
     */
    int findRentIndexById(int id);

    /*
     * 函数作用: 更新下一个可用编号为当前最大编号加1
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void updateNextId();

public:
    /*
     * 函数作用: 构造租赁管理器，初始化链表和编号
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    RentManager();

    /*
     * 函数作用: 从文件加载租赁记录数据到内存链表
     * 入参: 无
     * 返回值: 加载成功返回true，失败返回false
     * 异常提示: 无
     */
    bool loadFromFile();

    /*
     * 函数作用: 将内存链表中的租赁记录数据保存到文件
     * 入参: 无
     * 返回值: 保存成功返回true，失败返回false
     * 异常提示: 无
     */
    bool saveToFile();

    /*
     * 函数作用: 执行租车操作，创建新的租赁记录
     * 入参: vehicleId - 车辆编号；renterId - 租车人编号；rentDate - 租车日期；
     *       expectedReturnDate - 预计归还日期；deposit - 押金金额；
     *       dailyRate - 日租金；vehicleBrand - 车辆品牌；vehiclePlate - 车牌号；
     *       renterName - 租车人姓名；renterLicense - 驾照号
     * 返回值: 新创建的租赁记录编号
     * 异常提示: 无
     */
    int rentVehicle(int vehicleId, int renterId, const char* rentDate,
                    const char* expectedReturnDate, double deposit,
                    double dailyRate, const char* vehicleBrand,
                    const char* vehiclePlate, const char* renterName,
                    const char* renterLicense);

    /*
     * 函数作用: 执行还车操作，更新租赁记录状态
     * 入参: rentId - 租赁编号；returnDate - 归还日期；totalFee - 总费用
     * 返回值: 还车成功返回true，失败返回false
     * 异常提示: 无
     */
    bool returnVehicle(int rentId, const char* returnDate, double totalFee);

    /*
     * 函数作用: 按编号查找租赁记录
     * 入参: id - 租赁编号
     * 返回值: 找到返回租赁记录指针，未找到返回nullptr
     * 异常提示: 无
     */
    RentRecord* findRentById(int id);

    /*
     * 函数作用: 获取所有租赁记录的链表
     * 入参: 无
     * 返回值: 指向租赁记录链表的指针
     * 异常提示: 无
     */
    LinkedList<RentRecord>* getAllRentRecords();

    /*
     * 函数作用: 按车辆编号查询租赁记录
     * 入参: vehicleId - 车辆编号
     * 返回值: 匹配的租赁记录链表
     * 异常提示: 无
     */
    LinkedList<RentRecord> queryByVehicleId(int vehicleId);

    /*
     * 函数作用: 按租车人编号查询租赁记录
     * 入参: renterId - 租车人编号
     * 返回值: 匹配的租赁记录链表
     * 异常提示: 无
     */
    LinkedList<RentRecord> queryByRenterId(int renterId);

    /*
     * 函数作用: 按日期查询租赁记录
     * 入参: date - 查询日期
     * 返回值: 匹配的租赁记录链表
     * 异常提示: 无
     */
    LinkedList<RentRecord> queryByDate(const char* date);

    /*
     * 函数作用: 按状态查询租赁记录
     * 入参: status - 租赁状态枚举值
     * 返回值: 匹配的租赁记录链表
     * 异常提示: 无
     */
    LinkedList<RentRecord> queryByStatus(int status);

    /*
     * 函数作用: 按关键词模糊查询租赁记录
     * 入参: keyword - 搜索关键词
     * 返回值: 匹配的租赁记录链表
     * 异常提示: 无
     */
    LinkedList<RentRecord> queryFuzzy(const char* keyword);

    /*
     * 函数作用: 按品牌统计租赁次数
     * 入参: brand - 品牌名称
     * 返回值: 该品牌的租赁次数
     * 异常提示: 无
     */
    int countByBrand(const char* brand);

    /*
     * 函数作用: 按车辆类型统计租赁次数
     * 入参: type - 车辆类型
     * 返回值: 该类型的租赁次数
     * 异常提示: 无
     */
    int countByType(const char* type);

    /*
     * 函数作用: 按日期统计租赁次数
     * 入参: date - 查询日期
     * 返回值: 该日期的租赁次数
     * 异常提示: 无
     */
    int countByDate(const char* date);

    /*
     * 函数作用: 按状态统计租赁记录数量
     * 入参: status - 租赁状态枚举值
     * 返回值: 该状态的租赁记录数量
     * 异常提示: 无
     */
    int countByStatus(int status);

    /*
     * 函数作用: 获取租赁记录总数
     * 入参: 无
     * 返回值: 系统中租赁记录总数量
     * 异常提示: 无
     */
    int getTotalCount();

    /*
     * 函数作用: 获取当前进行中的租赁数量
     * 入参: 无
     * 返回值: 进行中的租赁数量
     * 异常提示: 无
     */
    int getActiveCount();

    /*
     * 函数作用: 计算所有已归还租赁的总营收
     * 入参: 无
     * 返回值: 总营收金额
     * 异常提示: 无
     */
    double getTotalRevenue();

    /*
     * 函数作用: 打印租赁统计信息
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void printStatistics();

    /*
     * 函数作用: 获取所有进行中的租赁记录
     * 入参: 无
     * 返回值: 进行中的租赁记录链表
     * 异常提示: 无
     */
    LinkedList<RentRecord> getActiveRents();

    /*
     * 函数作用: 获取所有已归还的租赁记录
     * 入参: 无
     * 返回值: 已归还的租赁记录链表
     * 异常提示: 无
     */
    LinkedList<RentRecord> getReturnedRents();
};

#endif
