/*
 * 程序功能: 汽车租赁管理系统 - 租车人管理实现
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 实现租车人数据的增删改查、文件持久化及统计分析功能
 */

#include "renter_manager.h"
#include "logger.h"
#include "utils.h"

/**
 * 函数作用: 构造函数，从文件加载租车人数据，若失败则初始化ID为1
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
RenterManager::RenterManager() {
    if (!loadFromFile()) {
        nextId = 1;
    }
}

/**
 * 函数作用: 从文件加载租车人数据到链表
 * 入参: 无
 * 返回值: true - 加载成功
 * 异常提示: 无
 */
bool RenterManager::loadFromFile() {
    FILE* fp = fopen(FILE_RENTER, "rb");
    if (fp == nullptr) {
        return true;
    }

    // 文件读写: 从文件加载数据
    Renter r;
    while (fread(&r, sizeof(Renter), 1, fp) == 1) {
        renters.append(r);
    }

    fclose(fp);
    updateNextId();
    return true;
}

/**
 * 函数作用: 保存租车人数据到文件
 * 入参: 无
 * 返回值: true - 保存成功; false - 保存失败
 * 异常提示: 无
 */
bool RenterManager::saveToFile() {
    FILE* fp = fopen(FILE_RENTER, "wb");
    if (fp == nullptr) {
        return false;
    }

    // 文件读写: 保存数据到文件
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        fwrite(&node->data, sizeof(Renter), 1, fp);
        node = node->next;
    }

    fclose(fp);
    return true;
}

/**
 * 函数作用: 按ID查找租车人在链表中的索引位置
 * 入参: id - 租车人ID
 * 返回值: 索引值(>=0); -1 - 未找到
 * 异常提示: 无
 */
int RenterManager::findRenterIndexById(int id) {
    // 链表中查找
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
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
 * 函数作用: 更新下一个可用的租车人ID（当前最大ID+1）
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void RenterManager::updateNextId() {
    int maxId = 0;
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.id > maxId) {
            maxId = node->data.id;
        }
        node = node->next;
    }
    nextId = maxId + 1;
}

/**
 * 函数作用: 添加新租车人，自动分配ID并初始化租车次数为0
 * 入参: r - 租车人信息引用
 * 返回值: true - 添加成功
 * 异常提示: 无
 */
bool RenterManager::addRenter(const Renter& r) {
    Renter newRenter = r;
    newRenter.id = nextId++;
    newRenter.rentCount = 0;
    renters.append(newRenter);
    // 文件读写: 保存数据到文件
    saveToFile();
    // 日志记录: 添加租车人
    Logger::logAdd("Renter", newRenter.id);
    return true;
}

/**
 * 函数作用: 按ID删除指定租车人
 * 入参: id - 租车人ID
 * 返回值: true - 删除成功; false - 未找到租车人
 * 异常提示: 无
 */
bool RenterManager::deleteRenter(int id) {
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            renters.removeNode(node);
            // 文件读写: 保存数据到文件
            saveToFile();
            // 日志记录: 删除租车人
            Logger::logDelete("Renter", id);
            return true;
        }
        node = node->next;
    }
    return false;
}

/**
 * 函数作用: 按ID修改租车人信息
 * 入参: id - 租车人ID; r - 新的租车人信息引用
 * 返回值: true - 修改成功; false - 未找到租车人
 * 异常提示: 无
 */
bool RenterManager::modifyRenter(int id, const Renter& r) {
    int index = findRenterIndexById(id);
    if (index == -1) {
        return false;
    }

    Renter* rPtr = renters.getAt(index);
    rPtr->id = id;
    strncpy(rPtr->name, r.name, MAX_NAME_LEN - 1);
    rPtr->name[MAX_NAME_LEN - 1] = '\0';
    rPtr->age = r.age;
    rPtr->gender = r.gender;
    strncpy(rPtr->phone, r.phone, MAX_PHONE_LEN - 1);
    rPtr->phone[MAX_PHONE_LEN - 1] = '\0';
    strncpy(rPtr->licenseNo, r.licenseNo, MAX_LICENSE_LEN - 1);
    rPtr->licenseNo[MAX_LICENSE_LEN - 1] = '\0';
    strncpy(rPtr->idCard, r.idCard, MAX_IDCARD_LEN - 1);
    rPtr->idCard[MAX_IDCARD_LEN - 1] = '\0';
    rPtr->drivingYears = r.drivingYears;
    rPtr->rentCount = r.rentCount;

    // 文件读写: 保存数据到文件
    saveToFile();
    // 日志记录: 修改租车人信息
    Logger::logModify("Renter", id);
    return true;
}

/**
 * 函数作用: 按ID查找租车人
 * 入参: id - 租车人ID
 * 返回值: 租车人指针 - 找到; nullptr - 未找到
 * 异常提示: 无
 */
Renter* RenterManager::findRenterById(int id) {
    // 链表中查找
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            return &node->data;
        }
        node = node->next;
    }
    return nullptr;
}

/**
 * 函数作用: 获取所有租车人链表指针
 * 入参: 无
 * 返回值: 租车人链表指针
 * 异常提示: 无
 */
LinkedList<Renter>* RenterManager::getAllRenters() {
    return &renters;
}

/**
 * 函数作用: 按姓名模糊查询租车人
 * 入参: name - 姓名关键字
 * 返回值: 匹配的租车人链表
 * 异常提示: 无
 */
LinkedList<Renter> RenterManager::queryByName(const char* name) {
    LinkedList<Renter> result;
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (strstr(node->data.name, name) != nullptr) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 按驾驶证号精确查询租车人
 * 入参: license - 驾驶证号
 * 返回值: 匹配的租车人链表
 * 异常提示: 无
 */
LinkedList<Renter> RenterManager::queryByLicense(const char* license) {
    LinkedList<Renter> result;
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.licenseNo, license) == 0) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 模糊查询租车人（匹配姓名、电话、驾驶证号、身份证号）
 * 入参: keyword - 查询关键字
 * 返回值: 匹配的租车人链表
 * 异常提示: 无
 */
LinkedList<Renter> RenterManager::queryFuzzy(const char* keyword) {
    LinkedList<Renter> result;
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (fuzzyMatch(node->data.name, keyword) ||
            fuzzyMatch(node->data.phone, keyword) ||
            fuzzyMatch(node->data.licenseNo, keyword) ||
            fuzzyMatch(node->data.idCard, keyword)) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

/**
 * 函数作用: 按性别统计租车人数量
 * 入参: gender - 性别（'M'男性 / 'F'女性）
 * 返回值: 该性别的租车人数量
 * 异常提示: 无
 */
int RenterManager::countByGender(char gender) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.gender == gender) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 统计驾龄大于等于指定年数的租车人数量
 * 入参: minYears - 最小驾龄年数
 * 返回值: 符合条件的租车人数量
 * 异常提示: 无
 */
int RenterManager::countByDrivingYears(int minYears) {
    int cnt = 0;
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.drivingYears >= minYears) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

/**
 * 函数作用: 获取租车人总数
 * 入参: 无
 * 返回值: 租车人总数
 * 异常提示: 无
 */
int RenterManager::getTotalCount() {
    return renters.size();
}

/**
 * 函数作用: 打印租车人统计信息（总数、性别分布、驾龄分布）
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void RenterManager::printStatistics() {
    int total = getTotalCount();
    int male = countByGender('M');
    int female = countByGender('F');
    int experienced = countByDrivingYears(3);
    int novice = total - experienced;

    int totalDrivingYears = 0;
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        totalDrivingYears += node->data.drivingYears;
        node = node->next;
    }
    double avgDrivingYears = total > 0 ? (double)totalDrivingYears / total : 0.0;

    // 日志记录: 打印租车人统计信息
    printf("\n===== 租车人统计信息 =====\n");
    printf("租车人总数: %d\n", total);
    printf("男性: %d  女性: %d\n", male, female);
    printf("驾龄>=3年: %d  驾龄<3年: %d\n", experienced, novice);
    printf("总驾龄: %d  平均驾龄: %.1f\n", totalDrivingYears, avgDrivingYears);
    printf("==========================\n");
}

/**
 * 函数作用: 增加指定租车人的租车次数
 * 入参: id - 租车人ID
 * 返回值: 无
 * 异常提示: 无
 */
void RenterManager::incrementRentCount(int id) {
    // 链表中查找
    // 动态链表操作: 遍历链表
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            node->data.rentCount++;
            // 文件读写: 保存数据到文件
            saveToFile();
            return;
        }
        node = node->next;
    }
}
