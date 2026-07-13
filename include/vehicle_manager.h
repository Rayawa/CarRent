#ifndef VEHICLE_MANAGER_H
#define VEHICLE_MANAGER_H

#include "common.h"
#include "vehicle.h"
#include "linked_list.h"

class VehicleManager {
private:
    LinkedList<Vehicle> vehicles;
    int nextId;

    int findVehicleIndexById(int id);
    void updateNextId();

public:
    VehicleManager();

    bool loadFromFile();
    bool saveToFile();

    bool addVehicle(const Vehicle& v);
    bool deleteVehicle(int id);
    bool modifyVehicle(int id, const Vehicle& v);
    Vehicle* findVehicleById(int id);
    LinkedList<Vehicle>* getAllVehicles();

    LinkedList<Vehicle> queryByBrand(const char* brand);
    LinkedList<Vehicle> queryByType(const char* type);
    LinkedList<Vehicle> queryByColor(const char* color);
    LinkedList<Vehicle> queryByStatus(int status);
    LinkedList<Vehicle> queryFuzzy(const char* keyword);

    int countByBrand(const char* brand);
    int countByType(const char* type);
    int countByColor(const char* color);
    int countByStatus(int status);

    int getTotalCount();
    int getAvailableCount();
    int getRentedCount();
    double getTotalValue();
    void printStatistics();
};

#endif
