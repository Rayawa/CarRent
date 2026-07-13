#ifndef RENT_RECORD_H
#define RENT_RECORD_H

#include "common.h"

struct RentRecord {
    int id;
    int vehicleId;
    int renterId;
    char rentDate[MAX_DATE_LEN];
    char expectedReturnDate[MAX_DATE_LEN];
    char actualReturnDate[MAX_DATE_LEN];
    double deposit;
    double dailyRate;
    double totalFee;
    int status;
    char vehicleBrand[MAX_BRAND_LEN];
    char vehiclePlate[MAX_PLATE_LEN];
    char renterName[MAX_NAME_LEN];
    char renterLicense[MAX_LICENSE_LEN];
};

void rentRecordInit(RentRecord* r);
void rentRecordPrint(const RentRecord* r);
void rentRecordPrintHeader();
void rentRecordPrintRow(const RentRecord* r);
const char* rentStatusStr(int status);

#endif
