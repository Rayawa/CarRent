#ifndef STATISTICS_H
#define STATISTICS_H

#include "common.h"

class VehicleManager;
class RenterManager;
class RentManager;

class Statistics {
public:
    static void showDashboard(VehicleManager* vm, RenterManager* rm, RentManager* rentm);
    static void showVehicleBarChart(VehicleManager* vm);
    static void showRentTrendChart(RentManager* rentm);
    static void showRentTypeBarChart(RentManager* rentm);
    static void showRevenueChart(RentManager* rentm);
};

#endif
