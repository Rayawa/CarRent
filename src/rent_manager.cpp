#include "rent_manager.h"
#include "logger.h"
#include "utils.h"

RentManager::RentManager() {
    if (!loadFromFile()) {
        nextId = 1;
    }
}

bool RentManager::loadFromFile() {
    FILE* fp = fopen(FILE_RENT, "rb");
    if (fp == nullptr) {
        return true;
    }

    RentRecord r;
    while (fread(&r, sizeof(RentRecord), 1, fp) == 1) {
        rentRecords.append(r);
    }

    fclose(fp);
    updateNextId();
    return true;
}

bool RentManager::saveToFile() {
    FILE* fp = fopen(FILE_RENT, "wb");
    if (fp == nullptr) {
        return false;
    }

    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        fwrite(&node->data, sizeof(RentRecord), 1, fp);
        node = node->next;
    }

    fclose(fp);
    return true;
}

int RentManager::findRentIndexById(int id) {
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

void RentManager::updateNextId() {
    int maxId = 0;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.id > maxId) {
            maxId = node->data.id;
        }
        node = node->next;
    }
    nextId = maxId + 1;
}

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
    saveToFile();
    Logger::logRent(r.id, vehicleId, renterId);
    return r.id;
}

bool RentManager::returnVehicle(int rentId, const char* returnDate, double totalFee) {
    RentRecord* r = findRentById(rentId);
    if (r == nullptr || r->status == RENT_RETURNED) {
        return false;
    }

    strncpy(r->actualReturnDate, returnDate, MAX_DATE_LEN - 1);
    r->actualReturnDate[MAX_DATE_LEN - 1] = '\0';
    r->totalFee = totalFee;
    r->status = RENT_RETURNED;

    saveToFile();
    Logger::logReturn(rentId, r->vehicleId, r->renterId, totalFee);
    return true;
}

RentRecord* RentManager::findRentById(int id) {
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            return &node->data;
        }
        node = node->next;
    }
    return nullptr;
}

LinkedList<RentRecord>* RentManager::getAllRentRecords() {
    return &rentRecords;
}

LinkedList<RentRecord> RentManager::queryByVehicleId(int vehicleId) {
    LinkedList<RentRecord> result;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.vehicleId == vehicleId) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<RentRecord> RentManager::queryByRenterId(int renterId) {
    LinkedList<RentRecord> result;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.renterId == renterId) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<RentRecord> RentManager::queryByDate(const char* date) {
    LinkedList<RentRecord> result;
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

LinkedList<RentRecord> RentManager::queryByStatus(int status) {
    LinkedList<RentRecord> result;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == status) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<RentRecord> RentManager::queryFuzzy(const char* keyword) {
    LinkedList<RentRecord> result;
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

int RentManager::countByBrand(const char* brand) {
    int cnt = 0;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.vehicleBrand, brand) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int RentManager::countByType(const char* type) {
    int cnt = 0;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.vehicleBrand, type) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int RentManager::countByDate(const char* date) {
    int cnt = 0;
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

int RentManager::countByStatus(int status) {
    int cnt = 0;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == status) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int RentManager::getTotalCount() {
    return rentRecords.size();
}

int RentManager::getActiveCount() {
    int cnt = 0;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == RENT_ACTIVE) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

double RentManager::getTotalRevenue() {
    double total = 0.0;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == RENT_RETURNED) {
            total += node->data.totalFee;
        }
        node = node->next;
    }
    return total;
}

void RentManager::printStatistics() {
    int total = getTotalCount();
    int active = getActiveCount();
    int returned = total - active;
    double revenue = getTotalRevenue();

    printf("\n===== 租车统计信息 =====\n");
    printf("租车记录总数: %d\n", total);
    printf("租用中: %d\n", active);
    printf("已归还: %d\n", returned);
    printf("总收入: %.2f 元\n", revenue);
    printf("========================\n");
}

LinkedList<RentRecord> RentManager::getActiveRents() {
    LinkedList<RentRecord> result;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == RENT_ACTIVE) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<RentRecord> RentManager::getReturnedRents() {
    LinkedList<RentRecord> result;
    ListNode<RentRecord>* node = rentRecords.getHead();
    while (node != nullptr) {
        if (node->data.status == RENT_RETURNED) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}
