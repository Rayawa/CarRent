#ifndef RENTER_H
#define RENTER_H

#include "common.h"

struct Renter {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char gender;
    char phone[MAX_PHONE_LEN];
    char licenseNo[MAX_LICENSE_LEN];
    char idCard[MAX_IDCARD_LEN];
    int drivingYears;
    int rentCount;
};

void renterInit(Renter* r);
void renterPrint(const Renter* r);
void renterPrintHeader();
void renterPrintRow(const Renter* r);

#endif
