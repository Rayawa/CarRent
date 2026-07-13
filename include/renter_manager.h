#ifndef RENTER_MANAGER_H
#define RENTER_MANAGER_H

#include "common.h"
#include "renter.h"
#include "linked_list.h"

class RenterManager {
private:
    LinkedList<Renter> renters;
    int nextId;

    int findRenterIndexById(int id);
    void updateNextId();

public:
    RenterManager();

    bool loadFromFile();
    bool saveToFile();

    bool addRenter(const Renter& r);
    bool deleteRenter(int id);
    bool modifyRenter(int id, const Renter& r);
    Renter* findRenterById(int id);
    LinkedList<Renter>* getAllRenters();

    LinkedList<Renter> queryByName(const char* name);
    LinkedList<Renter> queryByLicense(const char* license);
    LinkedList<Renter> queryFuzzy(const char* keyword);

    int countByGender(char gender);
    int countByDrivingYears(int minYears);

    int getTotalCount();
    void printStatistics();
    void incrementRentCount(int id);
};

#endif
