/*
 * 汽车租赁管理系统
 * 文件: menu1_vehicle.cpp
 * 功能: 车辆信息管理子菜单
 * 日期: 2026-07-16
 */
void menu1Vehicle() {
    while (true) {
        printf("\n1.添加车辆 2.删除车辆 3.修改车辆 4.显示所有 0.返回\n");
        int c = inputInt("请选择: ", 0, 4);
        if (c == 0) return;
        if (c == 4) { printAllVehicles(); pauseScreen(); continue; } // 直接打印
        if (c == 1) {
            Vehicle v{};
            initVehicle(v);
            while (true) {
                inputLine("车牌号: ", v.plateNo, MAX_PLATE_LEN);
                if (!isPlateNoDuplicate(v.plateNo)) break;
                printf("车牌号已存在，请重新输入\n");
            }
            inputLine("品牌: ", v.brand, MAX_BRAND_LEN);
            inputLine("类型: ", v.type, MAX_TYPE_LEN);
            inputLine("颜色: ", v.color, MAX_COLOR_LEN);
            inputLine("购买日期(YYYY-MM-DD): ", v.purchaseDate, MAX_DATE_LEN);
            inputLine("保险信息: ", v.insurance, MAX_INSURANCE_LEN);
            v.dailyRate = inputDouble("日租金: ", 0.0, 999999.0);
            v.deposit = inputDouble("押金: ", 0.0, 99999999.0);
            v.mileage = inputDouble("里程: ", 0.0, 9999999.0);
            addVehicle(v); // 输入v的所有信息（部分校验）并进入函数添加
            printf("已添加\n");
            pauseScreen();
        } else if (c == 2) {
            printAllVehicles();
            int id = inputInt("输入车辆ID: ", 1, 9999);
            printf(deleteVehicle(id) ? "已删除\n" : "没找到\n"); // 删除对应的id，如果返回false说明没找到
            pauseScreen();
        } else if (c == 3) {
            int id = inputInt("输入车辆ID: ", 1, 9999);
            Vehicle* p = findVehicle(id);
            if (!p) { printf("没找到\n"); pauseScreen(); continue; } // 判断到底有没有这辆车
            Vehicle v = *p;
            inputLine("车牌号: ", v.plateNo, MAX_PLATE_LEN);
            inputLine("品牌: ", v.brand, MAX_BRAND_LEN);
            inputLine("类型: ", v.type, MAX_TYPE_LEN);
            inputLine("颜色: ", v.color, MAX_COLOR_LEN);
            inputLine("购买日期: ", v.purchaseDate, MAX_DATE_LEN);
            inputLine("保险信息: ", v.insurance, MAX_INSURANCE_LEN);
            v.dailyRate = inputDouble("日租金: ", 0.0, 999999.0);
            v.deposit = inputDouble("押金: ", 0.0, 99999999.0);
            v.mileage = inputDouble("里程: ", 0.0, 9999999.0);
            printf(modifyVehicle(id, v) ? "已修改\n" : "失败\n"); // 输入所有信息并替换v的所有信息（部分校验）并进入函数添加，如果返回false说明失败了
            pauseScreen();
        }
    }
}
