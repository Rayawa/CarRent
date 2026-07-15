void menu5Query() {
    while (true) {
        printf("\n1. 查车辆 2. 查用户 3. 查租车记录 0. 返回\n");
        int c = inputInt("请选择: ", 0, 3);
        if (c == 0) return;
        // 查车辆：使用strstr在品牌和车牌字段中做子串模糊匹配
        if (c == 1) {
            char key[64];
            inputLine("输入品牌/车牌关键词: ", key, sizeof(key));
            printVehicleHeader();
            for (int i = 0; i < vehicleCount; i++) {
                if (strstr(vehicles[i].brand, key) || strstr(vehicles[i].plateNo, key)) {
                    printVehicleRow(vehicles[i]);
                }
            }
            pauseScreen();
        // 查用户：使用strstr在姓名和驾照号字段中做子串模糊匹配
        } else if (c == 2) {
            char key[64];
            inputLine("输入姓名/驾照关键词: ", key, sizeof(key));
            printRenterHeader();
            for (int i = 0; i < renterCount; i++) {
                if (strstr(renters[i].name, key) || strstr(renters[i].licenseNo, key)) {
                    printRenterRow(renters[i]);
                }
            }
            pauseScreen();
        // 查租车记录：将整数ID转为字符串后，在记录ID/车辆ID/用户ID中做子串模糊匹配
        } else if (c == 3) {
            char key[64];
            inputLine("输入租车ID/车辆ID/用户ID关键词: ", key, sizeof(key));
            printRentHeader();
            for (int i = 0; i < rentCount; i++) {
                char id1[16], id2[16], id3[16];
                snprintf(id1, sizeof(id1), "%d", rents[i].id);
                snprintf(id2, sizeof(id2), "%d", rents[i].vehicleId);
                snprintf(id3, sizeof(id3), "%d", rents[i].renterId);
                if (strstr(id1, key) || strstr(id2, key) || strstr(id3, key)) {
                    printRentRow(rents[i]);
                }
            }
            pauseScreen();
        }
    }
}
