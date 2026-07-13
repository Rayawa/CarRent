#ifndef VEHICLE_H
#define VEHICLE_H

#include "common.h"

struct Vehicle {
    int id;
    char plateNo[MAX_PLATE_LEN];
    char brand[MAX_BRAND_LEN];
    char type[MAX_TYPE_LEN];
    char color[MAX_COLOR_LEN];
    char purchaseDate[MAX_DATE_LEN];
    int status;
    double dailyRate;
    double mileage;
    char insurance[MAX_INSURANCE_LEN];
};

void vehicleInit(Vehicle* v);
void vehiclePrint(const Vehicle* v);
void vehiclePrintHeader();
void vehiclePrintRow(const Vehicle* v);
const char* vehicleStatusStr(int status);

#endif
