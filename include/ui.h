#ifndef UI_H
#define UI_H

#include "common.h"
#include "vehicle_manager.h"
#include "renter_manager.h"
#include "rent_manager.h"
#include "auth.h"

class UI {
private:
    VehicleManager vehicleManager;
    RenterManager renterManager;
    RentManager rentManager;
    AuthManager authManager;
    bool running;

    void mainMenu();
    void vehicleMenu();
    void renterMenu();
    void rentMenu();
    void returnMenu();
    void queryMenu();
    void statisticsMenu();
    void systemMenu();
    void extendedMenu();

    void handleAddVehicle();
    void handleDeleteVehicle();
    void handleModifyVehicle();
    void handleListVehicles();

    void handleAddRenter();
    void handleDeleteRenter();
    void handleModifyRenter();
    void handleListRenters();

    void handleRentVehicle();
    void handleReturnVehicle();
    void handlePrintReceipt();
    void handleListRentRecords();

    void handleQueryVehicles();
    void handleQueryRenters();
    void handleQueryRentRecords();

    void handleVehicleStatistics();
    void handleRenterStatistics();
    void handleRentStatistics();

    void handleChangePassword();
    void handleExportReport();
    void handleViewLog();
    void handleClearData();
    void handleFuzzySearch();

    void showBanner();

public:
    UI();
    void run();
};

#endif
