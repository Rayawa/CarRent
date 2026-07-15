//==========================菜单9：扩展功能====================
// 提供跨实体模糊搜索和车辆状态汇总等扩展功能
void menu9Extended() {
    while (true) {
        printf("\n1. 简单模糊搜索 2. 车辆状态汇总 0. 返回\n");
        int c = inputInt("请选择: ", 0, 2);
        if (c == 0) return;
        // 模糊搜索：用strstr在车辆品牌/车牌和用户名/驾照号中做跨实体子串匹配
        if (c == 1) {
            char key[64];
            inputLine("关键词: ", key, sizeof(key));
            printf("\n车辆匹配:\n");
            for (int i = 0; i < vehicleCount; i++) {
                if (strstr(vehicles[i].brand, key) || strstr(vehicles[i].plateNo, key)) {
                    printVehicleRow(vehicles[i]);
                }
            }
            printf("\n用户匹配:\n");
            for (int i = 0; i < renterCount; i++) {
                if (strstr(renters[i].name, key) || strstr(renters[i].licenseNo, key)) {
                    printRenterRow(renters[i]);
                }
            }
            pauseScreen();
        // 车辆状态汇总：按三种状态（可租/已租/维修）分别计数展示
        } else if (c == 2) {
            printf("可租: %d  已租: %d  维修: %d\n", countAvailableVehicles(), countRentedVehicles(), vehicleCount - countAvailableVehicles() - countRentedVehicles());
            pauseScreen();
        }
    }
}
