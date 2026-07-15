//==========================菜单3：租车业务办理====================
// 办理租车业务，通过车辆ID和用户ID关联创建租车记录
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
        // 办理租车：输入车辆ID和用户ID关联，校验日期格式合法性后生成租车记录
        int vehicleId = inputInt("车辆ID: ", 1, 9999);
        int renterId = inputInt("用户ID: ", 1, 9999);
        char rentDate[MAX_DATE_LEN];
        char expectedDate[MAX_DATE_LEN];
        inputLine("租车日期(YYYY-MM-DD): ", rentDate, MAX_DATE_LEN);
        inputLine("预计归还日期(YYYY-MM-DD): ", expectedDate, MAX_DATE_LEN);
        // 日期合法性校验：格式必须为YYYY-MM-DD，且月日在有效范围内
        if (!validDate(rentDate) || !validDate(expectedDate)) {
            printf("日期不对\n");
            pauseScreen();
            continue;
        }
        printf(addRentRecord(vehicleId, renterId, rentDate, expectedDate) ? "已办理租车\n" : "办理失败\n");
        pauseScreen();
    }
}
