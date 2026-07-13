#include "vehicle_manager.h"
#include "logger.h"
#include "utils.h"

VehicleManager::VehicleManager() {
    if (!loadFromFile()) {
        nextId = 1;
    }
}

bool VehicleManager::loadFromFile() {
    FILE* fp = fopen(FILE_VEHICLE, "rb");
    if (fp == nullptr) {
        return true;
    }

    Vehicle v;
    while (fread(&v, sizeof(Vehicle), 1, fp) == 1) {
        vehicles.append(v);
    }

    fclose(fp);
    updateNextId();
    return true;
}

bool VehicleManager::saveToFile() {
    FILE* fp = fopen(FILE_VEHICLE, "wb");
    if (fp == nullptr) {
        return false;
    }

    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        fwrite(&node->data, sizeof(Vehicle), 1, fp);
        node = node->next;
    }

    fclose(fp);
    return true;
}

int VehicleManager::findVehicleIndexById(int id) {
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

void VehicleManager::updateNextId() {
    int maxId = 0;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.id > maxId) {
            maxId = node->data.id;
        }
        node = node->next;
    }
    nextId = maxId + 1;
}

bool VehicleManager::addVehicle(const Vehicle& v) {
    Vehicle newVehicle = v;
    newVehicle.id = nextId++;
    newVehicle.status = STATUS_AVAILABLE;
    vehicles.append(newVehicle);
    saveToFile();
    Logger::logAdd("Vehicle", newVehicle.id);
    return true;
}

bool VehicleManager::deleteVehicle(int id) {
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            vehicles.removeNode(node);
            saveToFile();
            Logger::logDelete("Vehicle", id);
            return true;
        }
        node = node->next;
    }
    return false;
}

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

    saveToFile();
    Logger::logModify("Vehicle", id);
    return true;
}

Vehicle* VehicleManager::findVehicleById(int id) {
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.id == id) {
            return &node->data;
        }
        node = node->next;
    }
    return nullptr;
}

LinkedList<Vehicle>* VehicleManager::getAllVehicles() {
    return &vehicles;
}

LinkedList<Vehicle> VehicleManager::queryByBrand(const char* brand) {
    LinkedList<Vehicle> result;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.brand, brand) == 0) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<Vehicle> VehicleManager::queryByType(const char* type) {
    LinkedList<Vehicle> result;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.type, type) == 0) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<Vehicle> VehicleManager::queryByColor(const char* color) {
    LinkedList<Vehicle> result;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.color, color) == 0) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<Vehicle> VehicleManager::queryByStatus(int status) {
    LinkedList<Vehicle> result;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.status == status) {
            result.append(node->data);
        }
        node = node->next;
    }
    return result;
}

LinkedList<Vehicle> VehicleManager::queryFuzzy(const char* keyword) {
    LinkedList<Vehicle> result;
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

int VehicleManager::countByBrand(const char* brand) {
    int cnt = 0;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.brand, brand) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int VehicleManager::countByType(const char* type) {
    int cnt = 0;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.type, type) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int VehicleManager::countByColor(const char* color) {
    int cnt = 0;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (strcmp(node->data.color, color) == 0) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int VehicleManager::countByStatus(int status) {
    int cnt = 0;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.status == status) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int VehicleManager::getTotalCount() {
    return vehicles.size();
}

int VehicleManager::getAvailableCount() {
    int cnt = 0;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.status == STATUS_AVAILABLE) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

int VehicleManager::getRentedCount() {
    int cnt = 0;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        if (node->data.status == STATUS_RENTED) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

double VehicleManager::getTotalValue() {
    double total = 0.0;
    ListNode<Vehicle>* node = vehicles.getHead();
    while (node != nullptr) {
        total += node->data.dailyRate;
        node = node->next;
    }
    return total;
}

void VehicleManager::printStatistics() {
    int total = getTotalCount();
    int available = getAvailableCount();
    int rented = getRentedCount();
    int maintenance = countByStatus(STATUS_MAINTENANCE);
    double totalValue = getTotalValue();

    printf("\n===== 车辆统计信息 =====\n");
    printf("车辆总数: %d\n", total);
    printf("可租车辆: %d\n", available);
    printf("已租车辆: %d\n", rented);
    printf("维护车辆: %d\n", maintenance);
    printf("车队日总价值: %.2f\n", totalValue);
    printf("========================\n");
}
