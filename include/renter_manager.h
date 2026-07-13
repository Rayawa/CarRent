#ifndef RENTER_MANAGER_H
#define RENTER_MANAGER_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供租车人管理功能，包括租车人的增删改查、文件读写和统计查询
 */

#include "common.h"
#include "renter.h"
#include "linked_list.h"

class RenterManager {
private:
    LinkedList<Renter> renters;
    int nextId;

    /*
     * 函数作用: 按编号查找租车人在链表中的索引
     * 入参: id - 租车人编号
     * 返回值: 找到返回索引值，未找到返回-1
     * 异常提示: 无
     */
    int findRenterIndexById(int id);

    /*
     * 函数作用: 更新下一个可用编号为当前最大编号加1
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void updateNextId();

public:
    /*
     * 函数作用: 构造租车人管理器，初始化链表和编号
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    RenterManager();

    /*
     * 函数作用: 从文件加载租车人数据到内存链表
     * 入参: 无
     * 返回值: 加载成功返回true，失败返回false
     * 异常提示: 无
     */
    bool loadFromFile();

    /*
     * 函数作用: 将内存链表中的租车人数据保存到文件
     * 入参: 无
     * 返回值: 保存成功返回true，失败返回false
     * 异常提示: 无
     */
    bool saveToFile();

    /*
     * 函数作用: 添加一位新租车人到系统中
     * 入参: r - 待添加的租车人结构体引用
     * 返回值: 添加成功返回true，失败返回false
     * 异常提示: 无
     */
    bool addRenter(const Renter& r);

    /*
     * 函数作用: 按编号删除指定租车人
     * 入参: id - 待删除的租车人编号
     * 返回值: 删除成功返回true，失败返回false
     * 异常提示: 无
     */
    bool deleteRenter(int id);

    /*
     * 函数作用: 按编号修改指定租车人信息
     * 入参: id - 租车人编号；r - 包含新数据的租车人结构体引用
     * 返回值: 修改成功返回true，失败返回false
     * 异常提示: 无
     */
    bool modifyRenter(int id, const Renter& r);

    /*
     * 函数作用: 按编号查找租车人
     * 入参: id - 租车人编号
     * 返回值: 找到返回租车人指针，未找到返回nullptr
     * 异常提示: 无
     */
    Renter* findRenterById(int id);

    /*
     * 函数作用: 获取所有租车人的链表
     * 入参: 无
     * 返回值: 指向租车人链表的指针
     * 异常提示: 无
     */
    LinkedList<Renter>* getAllRenters();

    /*
     * 函数作用: 按姓名查询租车人
     * 入参: name - 租车人姓名
     * 返回值: 匹配的租车人链表
     * 异常提示: 无
     */
    LinkedList<Renter> queryByName(const char* name);

    /*
     * 函数作用: 按驾照号查询租车人
     * 入参: license - 驾照号
     * 返回值: 匹配的租车人链表
     * 异常提示: 无
     */
    LinkedList<Renter> queryByLicense(const char* license);

    /*
     * 函数作用: 按关键词模糊查询租车人
     * 入参: keyword - 搜索关键词
     * 返回值: 匹配的租车人链表
     * 异常提示: 无
     */
    LinkedList<Renter> queryFuzzy(const char* keyword);

    /*
     * 函数作用: 按性别统计租车人数量
     * 入参: gender - 性别字符('M'男/'F'女)
     * 返回值: 该性别租车人数量
     * 异常提示: 无
     */
    int countByGender(char gender);

    /*
     * 函数作用: 统计驾龄不小于指定年数的租车人数量
     * 入参: minYears - 最低驾龄年数
     * 返回值: 满足条件的租车人数量
     * 异常提示: 无
     */
    int countByDrivingYears(int minYears);

    /*
     * 函数作用: 获取租车人总数
     * 入参: 无
     * 返回值: 系统中租车人总数量
     * 异常提示: 无
     */
    int getTotalCount();

    /*
     * 函数作用: 打印租车人统计信息
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    void printStatistics();

    /*
     * 函数作用: 增加指定租车人的租车次数
     * 入参: id - 租车人编号
     * 返回值: 无
     * 异常提示: 无
     */
    void incrementRentCount(int id);
};

#endif
