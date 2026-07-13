/*
 * 程序功能: 汽车租赁管理系统 - 租赁业务管理实现
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 实现租赁数据的增删改查、文件持久化及统计分析功能
 */

#include "rent_manager.h"
#include "logger.h"
#include "utils.h"

/**
 * 函数作用: 构造函数，从文件加载租赁记录数据，若失败则初始化ID为1
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
RentManager::RentManager() {
    if (!loadFromFile()) {
        nextId = 1;
    }
}

/**
 * 函数作用: 从文件加载租赁记录数据到链表
 * 入参: 无
 * 返回值: true - 加载成功
 * 异常提示: 无
 */
bool RentManager::loadFromFile() {
    FILE* fp = fopen(FILE_RENT, "rb");
    if (fp == nullptr) {
        return true;
    }

    // 文件读写: 从文件加载数据
    RentRecord r;
    while (fread(&r, sizeof(RentRecord), 1, fp) == 1) {
        rentRecords.append(r);
    }

    fclose(fp);
    updateNextId();
    return true;
}

/**
 * 函数作用: 保存租赁记录数据到文件
 * 入参: 无
 * 返回值: true - 保存成功; false - 保存失败
 * 异常提示: 无
 */
bool RentManager::saveToFile() {
    FILE* fp = fopen(FILE_RENT, "wb");
    if (fp == nullptr) {
        return false;
    }

    // 文件读写: 保存数据到文件
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        fwrite(&node->data, sizeof(RentRecord), 1, fp);
        node = node->next;
    }

    fclose(fp);
    return true;
}

/**
 * 函数作用: 按ID查找租赁记录在链表中的索引位置
 * 入参: id - 租赁记录ID
 * 返回值: 索引值(>=0); -1 - 未找到
 * 异常提示: 无
 */
int RentManager::findRentIndexById(int id) {
    // 链表中查找
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    int index = 0;
    while (node != nullptr) {
        if (node->data.id == id) {
            return index;
        }
        node = node->next;
        index++;
    }
    return -1;
}

/**
 * 函数作用: 更新下一个可用的租赁记录ID（当前最大ID+1）
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void RentManager::updateNextId() {
    int maxId = 0;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.id > maxId) {
            maxId = node->data.id;
        }
        node = node->next;
    }
    nextId = maxId + 1;
}

/**
 * 函数作用: 创建新的租车记录，记录车辆和租车人信息，设置状态为租用中
 * 入参: vehicleId - 车辆ID; renterId - 租车人ID; rentDate - 租车日期;
 *        expectedReturnDate - 预计归还日期; deposit - 押金; dailyRate - 日租金;
 *        vehicleBrand - 车辆品牌; vehiclePlate - 车牌号; renterName - 租车人姓名;
 *        renterLicense - 租车人驾驶证号
 * 返回值: 新租赁记录的ID
 * 异常提示: 无
 */
int RentManager::rentVehicle(int vehicleId, int renterId, const char* rentDate,
                              const char* expectedReturnDate, double deposit,
                              double dailyRate, const char* vehicleBrand,
                              const char* vehiclePlate, const char* renterName,
                              const char* renterLicense) {
    RentRecord r;
    r.id = nextId++;
    r.vehicleId = vehicleId;
    r.renterId = renterId;
    strncpy(r.rentDate, rentDate, MAX_DATE_LEN - 1);
    r.rentDate[MAX_DATE_LEN - 1] = '\0';
    strncpy(r.expectedReturnDate, expectedReturnDate, MAX_DATE_LEN - 1);
    r.expectedReturnDate[MAX_DATE_LEN - 1] = '\0';
    r.actualReturnDate[0] = '\0';
    r.deposit = deposit;
    r.dailyRate = dailyRate;
    r.totalFee = 0;
    r.status = RENT_ACTIVE;
    strncpy(r.vehicleBrand, vehicleBrand, MAX_BRAND_LEN - 1);
    r.vehicleBrand[MAX_BRAND_LEN - 1] = '\0';
    strncpy(r.vehiclePlate, vehiclePlate, MAX_PLATE_LEN - 1);
    r.vehiclePlate[MAX_PLATE_LEN - 1] = '\0';
    strncpy(r.renterName, renterName, MAX_NAME_LEN - 1);
    r.renterName[MAX_NAME_LEN - 1] = '\0';
    strncpy(r.renterLicense, renterLicense, MAX_LICENSE_LEN - 1);
    r.renterLicense[MAX_LICENSE_LEN - 1] = '\0';

    rentRecords.append(r);
    // 文件读写: 保存数据到文件
    saveToFile();
    // 日志记录: 创建租车记录
    Logger::logRent(r.id, vehicleId, renterId);
    return r.id;
}

/**
 * 函数作用: 归还车辆，填写实际归还日期和总费用，更新状态为已归还
 * 入参: rentId - 租赁记录ID; returnDate - 实际归还日期; totalFee - 总费用
 * 返回值: true - 归还成功; false - 记录不存在或已归还
 * 异常提示: 无
 */
bool RentManager::returnVehicle(int rentId, const char* returnDate, double totalFee) {
    RentRecord* r = findRentById(rentId);
    if (r == nullptr || r->status == RENT_RETURNED) {
        return false;
    }

    strncpy(r->actualReturnDate, returnDate, MAX_DATE_LEN - 1);
    r->actualReturnDate[MAX_DATE_LEN - 1] = '\0';
    r->totalFee = totalFee;
    r->status = RENT_RETURNED;

    // 文件读写: 保存数据到文件
    saveToFile();
    // 日志记录: 归还车辆
    Logger::logReturn(rentId, r->vehicleId, r->renterId, totalFee);
    return true;
}

/**
 * 函数作用: 按ID查找租赁记录
 * 入参: id - 租赁记录ID
 * 返回值: 租赁记录指针 - 找到; nullptr - 未找到
 * 异常提示: 无
 */
RentRecord* RentManager::findRentById(int id) {
    // 链表中查找
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            return &node->data;
        }
        node = node->next;
    }
    return nullptr;
}

/**
 * 函数作用: 获取所有租赁记录链表指针
 * 入参: 无
 * 返回值: 租赁记录链表指针
 * 异常提示: 无
 */
LinkedList<RentRecord>* RentManager::getAllRentRecords() {
    return &rentRecords;
}

/**
 * 函数作用: 按车辆ID查询租赁记录
 * 入参: vehicleId - 车辆ID
 * 返回值: 匹配的租赁记录链表
 * 异常提示: 无
 */
LinkedList<RentRecord> RentManager::queryByVehicleId(int vehicleId) {
    LinkedList<RentRecord> result;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.vehicleId == vehicleId) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 按租车人ID查询租赁记录
 * 入参: renterId - 租车人ID
 * 返回值: 匹配的租赁记录链表
 * 异常提示: 无
 */
LinkedList<RentRecord> RentManager::queryByRenterId(int renterId) {
    LinkedList<RentRecord> result;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.renterId == renterId) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 按日期查询租赁记录（匹配租车日期、预计归还日期、实际归还日期）
 * 入参: date - 日期字符串
 * 返回值: 匹配的租赁记录链表
 * 异常提示: 无
 */
LinkedList<RentRecord> RentManager::queryByDate(const char* date) {
    LinkedList<RentRecord> result;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.rentDate, date) == 0 ||
            strcmp(node->data.expectedReturnDate, date) == 0 ||
            strcmp(node->data.actualReturnDate, date) == 0) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 按状态查询租赁记录
 * 入参: status - 租赁状态（租用中/已归还）
 * 返回值: 匹配的租赁记录链表
 * 异常提示: 无
 */
LinkedList<RentRecord> RentManager::queryByStatus(int status) {
    LinkedList<RentRecord> result;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == status) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 模糊查询租赁记录（匹配车辆品牌、车牌号、租车人姓名）
 * 入参: keyword - 查询关键字
 * 返回值: 匹配的租赁记录链表
 * 异常提示: 无
 */
LinkedList<RentRecord> RentManager::queryFuzzy(const char* keyword) {
    LinkedList<RentRecord> result;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (fuzzyMatch(node->data.vehicleBrand, keyword) ||
            fuzzyMatch(node->data.vehiclePlate, keyword) ||
            fuzzyMatch(node->data.renterName, keyword)) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 按车辆品牌统计租赁次数
 * 入参: brand - 车辆品牌
 * 返回值: 租赁次数
 * 异常提示: 无
 */
int RentManager::countByBrand(const char* brand) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.vehicleBrand, brand) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 按车辆品牌（类型）统计租赁次数
 * 入参: type - 车辆品牌/类型
 * 返回值: 租赁次数
 * 异常提示: 无
 */
int RentManager::countByType(const char* type) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.vehicleBrand, type) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 按日期统计租赁记录数量
 * 入参: date - 日期字符串
 * 返回值: 租赁记录数量
 * 异常提示: 无
 */
int RentManager::countByDate(const char* date) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.rentDate, date) == 0 ||
            strcmp(node->data.expectedReturnDate, date) == 0 ||
            strcmp(node->data.actualReturnDate, date) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 按状态统计租赁记录数量
 * 入参: status - 租赁状态
 * 返回值: 租赁记录数量
 * 异常提示: 无
 */
int RentManager::countByStatus(int status) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == status) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 获取租赁记录总数
 * 入参: 无
 * 返回值: 租赁记录总数
 * 异常提示: 无
 */
int RentManager::getTotalCount() {
    return rentRecords.size();
}

/**
 * 函数作用: 获取进行中的租赁记录数量
 * 入参: 无
 * 返回值: 进行中的租赁记录数量
 * 异常提示: 无
 */
int RentManager::getActiveCount() {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == RENT_ACTIVE) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 获取已归还租赁的总收入
 * 入参: 无
 * 返回值: 总收入金额
 * 异常提示: 无
 */
double RentManager::getTotalRevenue() {
    double total = 0.0;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == RENT_RETURNED) {
            total += node->data.totalFee;
        }
        node = node->next;
    }
    return total;
}

/**
 * 函数作用: 打印租赁统计信息（总数、租用中、已归还、总收入）
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void RentManager::printStatistics() {
    int total = getTotalCount();
    int active = getActiveCount();
    int returned = total - active;
    double revenue = getTotalRevenue();

    // 日志记录: 打印租赁统计信息
    printf("\n===== 租车统计信息 =====\n");
    printf("租车记录总数: %d\n", total);
    printf("租用中: %d\n", active);
    printf("已归还: %d\n", returned);
    printf("总收入: %.2f 元\n", revenue);
    printf("========================\n");
}

/**
 * 函数作用: 获取所有进行中的租赁记录
 * 入参: 无
 * 返回值: 进行中的租赁记录链表
 * 异常提示: 无
 */
LinkedList<RentRecord> RentManager::getActiveRents() {
    LinkedList<RentRecord> result;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == RENT_ACTIVE) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 获取所有已归还的租赁记录
 * 入参: 无
 * 返回值: 已归还的租赁记录链表
 * 异常提示: 无
 */
LinkedList<RentRecord> RentManager::getReturnedRents() {
    LinkedList<RentRecord> result;
    // 动态链表操作: 遍历链表
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == RENT_RETURNED) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}
