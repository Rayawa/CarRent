#include "renter_manager.h"
#include "logger.h"
#include "utils.h"

RenterManager::RenterManager() {
    if (!loadFromFile()) {
        nextId = 1;
    }
}

bool RenterManager::loadFromFile() {
    FILE* fp = fopen(FILE_RENTER, "rb");
    if (fp == nullptr) {
        return true;
    }

    Renter r;
    while (fread(&r, sizeof(Renter), 1, fp) == 1) {
        renters.append(r);
    }

    fclose(fp);
    updateNextId();
    return true;
}

bool RenterManager::saveToFile() {
    FILE* fp = fopen(FILE_RENTER, "wb");
    if (fp == nullptr) {
        return false;
    }

    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        fwrite(&node->data, sizeof(Renter), 1, fp);
        node = node->next;
    }

    fclose(fp);
    return true;
}

int RenterManager::findRenterIndexById(int id) {
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

void RenterManager::updateNextId() {
    int maxId = 0;
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.id > maxId) {
            maxId = node->data.id;
        }
        node = node->next;
    }
    nextId = maxId + 1;
}

bool RenterManager::addRenter(const Renter& r) {
    Renter newRenter = r;
    newRenter.id = nextId++;
    newRenter.rentCount = 0;
    renters.append(newRenter);
    saveToFile();
    Logger::logAdd("Renter", newRenter.id);
    return true;
}

bool RenterManager::deleteRenter(int id) {
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            renters.removeNode(node);
            saveToFile();
            Logger::logDelete("Renter", id);
            return true;
        }
        node = node->next;
    }
    return false;
}

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

    saveToFile();
    Logger::logModify("Renter", id);
    return true;
}

Renter* RenterManager::findRenterById(int id) {
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            return &node->data;
        }
        node = node->next;
    }
    return nullptr;
}

LinkedList<Renter>* RenterManager::getAllRenters() {
    return &renters;
}

LinkedList<Renter> RenterManager::queryByName(const char* name) {
    LinkedList<Renter> result;
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (strstr(node->data.name, name) != nullptr) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<Renter> RenterManager::queryByLicense(const char* license) {
    LinkedList<Renter> result;
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.licenseNo, license) == 0) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<Renter> RenterManager::queryFuzzy(const char* keyword) {
    LinkedList<Renter> result;
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

int RenterManager::countByGender(char gender) {
    int cnt = 0;
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.gender == gender) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int RenterManager::countByDrivingYears(int minYears) {
    int cnt = 0;
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.drivingYears >= minYears) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int RenterManager::getTotalCount() {
    return renters.size();
}

void RenterManager::printStatistics() {
    int total = getTotalCount();
    int male = countByGender('M');
    int female = countByGender('F');
    int experienced = countByDrivingYears(3);
    int novice = total - experienced;

    int totalDrivingYears = 0;
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        totalDrivingYears += node->data.drivingYears;
        node = node->next;
    }
    double avgDrivingYears = total > 0 ? (double)totalDrivingYears / total : 0.0;

    printf("\n===== 租车人统计信息 =====\n");
    printf("租车人总数: %d\n", total);
    printf("男性: %d  女性: %d\n", male, female);
    printf("驾龄>=3年: %d  驾龄<3年: %d\n", experienced, novice);
    printf("总驾龄: %d  平均驾龄: %.1f\n", totalDrivingYears, avgDrivingYears);
    printf("==========================\n");
}

void RenterManager::incrementRentCount(int id) {
    ListNode<Renter>* node = renters.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            node->data.rentCount++;
            saveToFile();
            return;
        }
        node = node->next;
    }
}
