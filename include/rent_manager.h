#ifndef RENT_MANAGER_H
#define RENT_MANAGER_H

#include "common.h"
#include "rent_record.h"
#include "linked_list.h"

class VehicleManager;
class RenterManager;

class RentManager {
private:
    LinkedList<RentRecord> rentRecords;
    int nextId;

    int findRentIndexById(int id);
    void updateNextId();

public:
    RentManager();

    bool loadFromFile();
    bool saveToFile();

    int rentVehicle(int vehicleId, int renterId, const char* rentDate,
                    const char* expectedReturnDate, double deposit,
                    double dailyRate, const char* vehicleBrand,
                    const char* vehiclePlate, const char* renterName,
                    const char* renterLicense);
    bool returnVehicle(int rentId, const char* returnDate, double totalFee);
    RentRecord* findRentById(int id);
    LinkedList<RentRecord>* getAllRentRecords();

    LinkedList<RentRecord> queryByVehicleId(int vehicleId);
    LinkedList<RentRecord> queryByRenterId(int renterId);
    LinkedList<RentRecord> queryByDate(const char* date);
    LinkedList<RentRecord> queryByStatus(int status);
    LinkedList<RentRecord> queryFuzzy(const char* keyword);

    int countByBrand(const char* brand);
    int countByType(const char* type);
    int countByDate(const char* date);
    int countByStatus(int status);

    int getTotalCount();
    int getActiveCount();
    double getTotalRevenue();
    void printStatistics();

    LinkedList<RentRecord> getActiveRents();
    LinkedList<RentRecord> getReturnedRents();
};

#endif
