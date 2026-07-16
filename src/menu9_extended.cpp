/*
 * 汽车租赁管理系统
 * 文件: menu9_extended.cpp  功能: 扩展功能子菜单
 * 作者: 孙老师组     日期: 2026-07
 */
void menu9Extended() {
    while (true) {
        printf("\n1.模糊搜索 2.车辆状态汇总 3.品牌分布图 0.返回\n");
        int c = inputInt("请选择: ", 0, 3);
        if (c == 0) return;
        if (c == 1) {
            char key[64];
            inputLine("关键词: ", key, sizeof(key));
            printf("\n车辆匹配:\n"); printVehicleHeader();
            VehicleNode* vc = vehicleHead;
            while (vc) {
                if (strstr(vc->data.brand, key) || strstr(vc->data.plateNo, key)) printVehicleRow(vc->data);
                vc = vc->next;
            }
            printf("\n用户匹配:\n"); printRenterHeader();
            RenterNode* rc = renterHead;
            while (rc) {
                if (strstr(rc->data.name, key) || strstr(rc->data.licenseNo, key)) printRenterRow(rc->data);
                rc = rc->next;
            }
            pauseScreen();
        } else if (c == 2) {
            int a = countAvailableVehicles(), r = countRentedVehicles(), m = vehicleCount - a - r;
            char sl[3][32]; int sv[3];
            strncpy(sl[0], "可租", 31); strncpy(sl[1], "已租", 31); strncpy(sl[2], "维修", 31);
            sv[0] = a; sv[1] = r; sv[2] = m;
            drawBarChart(sl, sv, 3);
            pauseScreen();
        } else if (c == 3) {
            char labels[50][32]; int values[50];
            int n = countVehiclesByBrand(labels, values, 50);
            printf("\n车辆品牌分布:\n");
            drawBarChart(labels, values, n);
            pauseScreen();
        }
    }
}
