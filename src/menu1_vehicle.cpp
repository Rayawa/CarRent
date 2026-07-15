void menu1Vehicle() {
    while (true) {
        printf("\n1. 添加车辆 2. 删除车辆 3. 修改车辆 4. 显示所有 0. 返回\n");
        int c = inputInt("请选择: ", 0, 4);
        if (c == 0) return;
        if (c == 4) {
            printAllVehicles();
            pauseScreen();
            continue;
        }
        // 添加车辆：逐字段录入后追加到数组末尾
        if (c == 1) {
            Vehicle v;
            initVehicle(v);
            inputLine("车牌号: ", v.plateNo, MAX_PLATE_LEN);
            inputLine("品牌: ", v.brand, MAX_BRAND_LEN);
            inputLine("类型: ", v.type, MAX_TYPE_LEN);
            inputLine("颜色: ", v.color, MAX_COLOR_LEN);
            inputLine("购买日期(YYYY-MM-DD): ", v.purchaseDate, MAX_DATE_LEN);
            inputLine("保险信息: ", v.insurance, MAX_INSURANCE_LEN);
            v.dailyRate = inputDouble("日租金: ", 0.0, 999999.0);
            v.mileage = inputDouble("里程: ", 0.0, 9999999.0);
            addVehicle(v);
            printf("已添加\n");
            pauseScreen();
        // 删除车辆：先展示全部车辆，通过ID定位后从数组中移除（后续元素前移覆盖）
        } else if (c == 2) {
            printAllVehicles();
            int id = inputInt("输入车辆ID: ", 1, 9999);
            printf(deleteVehicle(id) ? "已删除\n" : "没找到\n");
            pauseScreen();
        // 修改车辆：通过ID查找车辆，展示当前值后覆盖更新
        } else if (c == 3) {
            int id = inputInt("输入车辆ID: ", 1, 9999);
            Vehicle* p = findVehicle(id);
            if (!p) { printf("没找到\n"); pauseScreen(); continue; }
            Vehicle v = *p;
            inputLine("车牌号: ", v.plateNo, MAX_PLATE_LEN);
            inputLine("品牌: ", v.brand, MAX_BRAND_LEN);
            inputLine("类型: ", v.type, MAX_TYPE_LEN);
            inputLine("颜色: ", v.color, MAX_COLOR_LEN);
            inputLine("购买日期: ", v.purchaseDate, MAX_DATE_LEN);
            inputLine("保险信息: ", v.insurance, MAX_INSURANCE_LEN);
            v.dailyRate = inputDouble("日租金: ", 0.0, 999999.0);
            v.mileage = inputDouble("里程: ", 0.0, 9999999.0);
            printf(modifyVehicle(id, v) ? "已修改\n" : "失败\n");
            pauseScreen();
        }
    }
}
