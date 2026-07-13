/*
 * 程序功能: 汽车租赁管理系统 - 车辆管理实现
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 实现车辆数据的增删改查、文件持久化及统计分析功能
 */

#include "vehicle_manager.h"
#include "logger.h"
#include "utils.h"

/**
 * 函数作用: 构造函数，从文件加载车辆数据，若失败则初始化ID为1
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
VehicleManager::VehicleManager() {
    if (!loadFromFile()) {
        nextId = 1;
    }
}

/**
 * 函数作用: 从文件加载车辆数据到链表
 * 入参: 无
 * 返回值: true - 加载成功
 * 异常提示: 无
 */
bool VehicleManager::loadFromFile() {
    FILE* fp = fopen(FILE_VEHICLE, "rb");
    if (fp == nullptr) {
        return true;
    }

    // 文件读写: 从文件加载数据
    Vehicle v;
    while (fread(&v, sizeof(Vehicle), 1, fp) == 1) {
        vehicles.append(v);
    }

    fclose(fp);
    updateNextId();
    return true;
}

/**
 * 函数作用: 保存车辆数据到文件
 * 入参: 无
 * 返回值: true - 保存成功; false - 保存失败
 * 异常提示: 无
 */
bool VehicleManager::saveToFile() {
    FILE* fp = fopen(FILE_VEHICLE, "wb");
    if (fp == nullptr) {
        return false;
    }

    // 文件读写: 保存数据到文件
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        fwrite(&node->data, sizeof(Vehicle), 1, fp);
        node = node->next;
    }

    fclose(fp);
    return true;
}

/**
 * 函数作用: 按ID查找车辆在链表中的索引位置
 * 入参: id - 车辆ID
 * 返回值: 索引值(>=0); -1 - 未找到
 * 异常提示: 无
 */
int VehicleManager::findVehicleIndexById(int id) {
    // 链表中查找
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
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
 * 函数作用: 更新下一个可用的车辆ID（当前最大ID+1）
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void VehicleManager::updateNextId() {
    int maxId = 0;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.id > maxId) {
            maxId = node->data.id;
        }
        node = node->next;
    }
    nextId = maxId + 1;
}

/**
 * 函数作用: 添加新车辆，自动分配ID并设为可租状态
 * 入参: v - 车辆信息引用
 * 返回值: true - 添加成功
 * 异常提示: 无
 */
bool VehicleManager::addVehicle(const Vehicle& v) {
    Vehicle newVehicle = v;
    newVehicle.id = nextId++;
    newVehicle.status = STATUS_AVAILABLE;
    vehicles.append(newVehicle);
    // 文件读写: 保存数据到文件
    saveToFile();
    // 日志记录: 添加车辆
    Logger::logAdd("Vehicle", newVehicle.id);
    return true;
}

/**
 * 函数作用: 按ID删除指定车辆
 * 入参: id - 车辆ID
 * 返回值: true - 删除成功; false - 未找到车辆
 * 异常提示: 无
 */
bool VehicleManager::deleteVehicle(int id) {
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            vehicles.removeNode(node);
            // 文件读写: 保存数据到文件
            saveToFile();
            // 日志记录: 删除车辆
            Logger::logDelete("Vehicle", id);
            return true;
        }
        node = node->next;
    }
    return false;
}

/**
 * 函数作用: 按ID修改车辆信息
 * 入参: id - 车辆ID; v - 新的车辆信息引用
 * 返回值: true - 修改成功; false - 未找到车辆
 * 异常提示: 无
 */
bool VehicleManager::modifyVehicle(int id, const Vehicle& v) {
    int index = findVehicleIndexById(id);
    if (index == -1) {
        return false;
    }

    Vehicle* vPtr = vehicles.getAt(index);
    vPtr->id = id;
    strncpy(vPtr->plateNo, v.plateNo, MAX_PLATE_LEN - 1);
    vPtr->plateNo[MAX_PLATE_LEN - 1] = '\0';
    strncpy(vPtr->brand, v.brand, MAX_BRAND_LEN - 1);
    vPtr->brand[MAX_BRAND_LEN - 1] = '\0';
    strncpy(vPtr->type, v.type, MAX_TYPE_LEN - 1);
    vPtr->type[MAX_TYPE_LEN - 1] = '\0';
    strncpy(vPtr->color, v.color, MAX_COLOR_LEN - 1);
    vPtr->color[MAX_COLOR_LEN - 1] = '\0';
    strncpy(vPtr->purchaseDate, v.purchaseDate, MAX_DATE_LEN - 1);
    vPtr->purchaseDate[MAX_DATE_LEN - 1] = '\0';
    vPtr->status = v.status;
    vPtr->dailyRate = v.dailyRate;
    vPtr->mileage = v.mileage;
    strncpy(vPtr->insurance, v.insurance, MAX_INSURANCE_LEN - 1);
    vPtr->insurance[MAX_INSURANCE_LEN - 1] = '\0';

    // 文件读写: 保存数据到文件
    saveToFile();
    // 日志记录: 修改车辆信息
    Logger::logModify("Vehicle", id);
    return true;
}

/**
 * 函数作用: 按ID查找车辆
 * 入参: id - 车辆ID
 * 返回值: 车辆指针 - 找到; nullptr - 未找到
 * 异常提示: 无
 */
Vehicle* VehicleManager::findVehicleById(int id) {
    // 链表中查找
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            return &node->data;
        }
        node = node->next;
    }
    return nullptr;
}

/**
 * 函数作用: 获取所有车辆链表指针
 * 入参: 无
 * 返回值: 车辆链表指针
 * 异常提示: 无
 */
LinkedList<Vehicle>* VehicleManager::getAllVehicles() {
    return &vehicles;
}

/**
 * 函数作用: 按品牌查询车辆
 * 入参: brand - 品牌名称
 * 返回值: 匹配的车辆链表
 * 异常提示: 无
 */
LinkedList<Vehicle> VehicleManager::queryByBrand(const char* brand) {
    LinkedList<Vehicle> result;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.brand, brand) == 0) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 按车型查询车辆
 * 入参: type - 车型
 * 返回值: 匹配的车辆链表
 * 异常提示: 无
 */
LinkedList<Vehicle> VehicleManager::queryByType(const char* type) {
    LinkedList<Vehicle> result;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.type, type) == 0) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 按颜色查询车辆
 * 入参: color - 颜色
 * 返回值: 匹配的车辆链表
 * 异常提示: 无
 */
LinkedList<Vehicle> VehicleManager::queryByColor(const char* color) {
    LinkedList<Vehicle> result;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.color, color) == 0) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 按状态查询车辆
 * 入参: status - 车辆状态（可租/已租/维护）
 * 返回值: 匹配的车辆链表
 * 异常提示: 无
 */
LinkedList<Vehicle> VehicleManager::queryByStatus(int status) {
    LinkedList<Vehicle> result;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.status == status) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 模糊查询车辆（匹配品牌、车型、颜色、车牌号）
 * 入参: keyword - 查询关键字
 * 返回值: 匹配的车辆链表
 * 异常提示: 无
 */
LinkedList<Vehicle> VehicleManager::queryFuzzy(const char* keyword) {
    LinkedList<Vehicle> result;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (fuzzyMatch(node->data.brand, keyword) ||
            fuzzyMatch(node->data.type, keyword) ||
            fuzzyMatch(node->data.color, keyword) ||
            fuzzyMatch(node->data.plateNo, keyword)) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 统计指定品牌的车辆数量
 * 入参: brand - 品牌名称
 * 返回值: 车辆数量
 * 异常提示: 无
 */
int VehicleManager::countByBrand(const char* brand) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.brand, brand) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 统计指定车型的车辆数量
 * 入参: type - 车型
 * 返回值: 车辆数量
 * 异常提示: 无
 */
int VehicleManager::countByType(const char* type) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.type, type) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 统计指定颜色的车辆数量
 * 入参: color - 颜色
 * 返回值: 车辆数量
 * 异常提示: 无
 */
int VehicleManager::countByColor(const char* color) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.color, color) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 统计指定状态的车辆数量
 * 入参: status - 车辆状态
 * 返回值: 车辆数量
 * 异常提示: 无
 */
int VehicleManager::countByStatus(int status) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.status == status) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 获取车辆总数
 * 入参: 无
 * 返回值: 车辆总数
 * 异常提示: 无
 */
int VehicleManager::getTotalCount() {
    return vehicles.size();
}

/**
 * 函数作用: 获取可租车辆数量
 * 入参: 无
 * 返回值: 可租车辆数量
 * 异常提示: 无
 */
int VehicleManager::getAvailableCount() {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.status == STATUS_AVAILABLE) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 获取已租车辆数量
 * 入参: 无
 * 返回值: 已租车辆数量
 * 异常提示: 无
 */
int VehicleManager::getRentedCount() {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.status == STATUS_RENTED) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 获取车队日总价值（所有车辆日租金总和）
 * 入参: 无
 * 返回值: 日总价值
 * 异常提示: 无
 */
double VehicleManager::getTotalValue() {
    double total = 0.0;
    // 动态链表操作: 遍历链表
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        total += node->data.dailyRate;
        node = node->next;
    }
    return total;
}

/**
 * 函数作用: 打印车辆统计信息（总数、可租、已租、维护、日总价值）
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void VehicleManager::printStatistics() {
    int total = getTotalCount();
    int available = getAvailableCount();
    int rented = getRentedCount();
    int maintenance = countByStatus(STATUS_MAINTENANCE);
    double totalValue = getTotalValue();

    // 日志记录: 打印车辆统计信息
    printf("\n===== 车辆统计信息 =====\n");
    printf("车辆总数: %d\n", total);
    printf("可租车辆: %d\n", available);
    printf("已租车辆: %d\n", rented);
    printf("维护车辆: %d\n", maintenance);
    printf("车队日总价值: %.2f\n", totalValue);
    printf("========================\n");
}
