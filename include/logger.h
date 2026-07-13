#ifndef LOGGER_H
#define LOGGER_H

#include "common.h"

class Logger {
public:
    static void logOperation(const char* operation);
    static void logAdd(const char* entity, int id);
    static void logDelete(const char* entity, int id);
    static void logModify(const char* entity, int id);
    static void logRent(int rentId, int vehicleId, int renterId);
    static void logReturn(int rentId, int vehicleId, int renterId, double fee);
    static void logLogin(bool success);
    static void showLog();
};

#endif
