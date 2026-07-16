/*
 * 汽车租赁管理系统
 * 文件: menu9_extended.cpp  功能: 扩展功能子菜单
 * 作者: 孙老师组     日期: 2026-07
 */
//==========================菜单9：扩展功能====================
// 跨实体模糊搜索/车辆状态汇总/ASCII柱状图展示
void menu9Extended() {
    while (true) {
        printf("\n1.模糊搜索 2.车辆状态汇总 3.品牌分布图 0.返回\n");
        int c = inputInt("请选择: ", 0, 3);
        if (c == 0) return;
        // 模糊搜索：strstr在车辆品牌/车牌和用户名/驾照号中跨实体匹配
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
        // 车辆状态汇总：三种状态分别计数
        } else if (c == 2) {
            int a = countAvailableVehicles(), r = countRentedVehicles(), m = vehicleCount - a - r;
            printf("\n可租: %d  已租: %d  维修: %d\n", a, r, m);
            int total = vehicleCount > 0 ? vehicleCount : 1;
            printf("可租 "); for (int i = 0; i < a * 30 / total; i++) printf("#"); printf(" %d\n", a);
            printf("已租 "); for (int i = 0; i < r * 30 / total; i++) printf("#"); printf(" %d\n", r);
            printf("维修 "); for (int i = 0; i < m * 30 / total; i++) printf("#"); printf(" %d\n", m);
            pauseScreen();
        // 品牌分布图：按品牌分组绘制ASCII柱状图
        } else if (c == 3) {
            char labels[50][32]; int values[50];
            int n = countVehiclesByBrand(labels, values, 50);
            printf("\n车辆品牌分布:\n");
            const char* labelPtrs[50];
            for (int i = 0; i < n; i++) labelPtrs[i] = labels[i];
            drawBarChart(labelPtrs, values, n);
            pauseScreen();
        }
    }
}
