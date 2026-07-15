void menu3Rent() {
    while (true) {
        printf("\n1. 办理租车 2. 显示租车记录 0. 返回\n");
        int c = inputInt("请选择: ", 0, 2);
        if (c == 0) return;
        if (c == 2) {
            printAllRents();
            pauseScreen();
            continue;
        }
        int vehicleId = inputInt("车辆ID: ", 1, 9999);
        int renterId = inputInt("用户ID: ", 1, 9999);
        char rentDate[MAX_DATE_LEN];
        char expectedDate[MAX_DATE_LEN];
        inputLine("租车日期(YYYY-MM-DD): ", rentDate, MAX_DATE_LEN);
        inputLine("预计归还日期(YYYY-MM-DD): ", expectedDate, MAX_DATE_LEN);
        if (!validDate(rentDate) || !validDate(expectedDate)) {
            printf("日期不对\n");
            pauseScreen();
            continue;
        }
        printf(addRentRecord(vehicleId, renterId, rentDate, expectedDate) ? "已办理租车\n" : "办理失败\n");
        pauseScreen();
    }
}
