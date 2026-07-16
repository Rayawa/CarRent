/*
 * 汽车租赁管理系统
 * 文件: menu6_statistics.cpp
 * 功能: 统计汇总子菜单
 * 日期: 2026-07
 */
void menu6Statistics() {
    while (true) {
        printf("\n1.系统概览 2.车辆统计 3.用户统计 4.租车统计 5.输出全部信息 0.返回\n");
        int c = inputInt("请选择: ", 0, 5);
        if (c == 0) return;
        if (c == 1) {
            // 系统概览：打印总数统计→车辆状态柱状图(可租/已租/维修)→品牌分布柱状图
            printStatistics();
            // 可租车辆数a，已租车辆数r，维修车辆数m=vehicleCount-a-r
            int a = countAvailableVehicles(), r = countRentedVehicles(), m = vehicleCount - a - r;
            printf("\n车辆状态:\n");
            // 标签数组：存储 "可租"、"已租"、"维修"，数值数组：存储对应的数量
            char sl[3][32]; int sv[3];
            strncpy(sl[0], "可租", 31); strncpy(sl[1], "已租", 31); strncpy(sl[2], "维修", 31);
            sv[0] = a; sv[1] = r; sv[2] = m;
            drawBarChart(sl, sv, 3);   // ASCII柱状图：找到最大值后各值按比例绘制#号
            char labels[50][32]; int values[50];
            int n = countVehiclesByBrand(labels, values, 50);   // 遍历链表→去重分组→计数
            printf("\n品牌分布:\n");
            drawBarChart(labels, values, n);
            pauseScreen();
        } else if (c == 2) {
            // 车辆统计：按品牌/类型/颜色分组→ASCII柱状图展示
            printf("\n1.按品牌 2.按类型 3.按颜色 0.返回\n");
            int sc = inputInt("请选择: ", 0, 3);
            if (sc == 0) continue;
            char labels[50][32]; int values[50]; int n = 0;
            if (sc == 1) n = countVehiclesByBrand(labels, values, 50);   // 遍历链表→去重→计数
            else if (sc == 2) n = countVehiclesByType(labels, values, 50);
            else n = countVehiclesByColor(labels, values, 50);
            printf("\n");
            drawBarChart(labels, values, n);
            pauseScreen();
        } else if (c == 3) {
            // 用户统计：按性别(M/F)或驾龄分段(0-3/4-10/10+)分组
            printf("\n1.按性别 2.按驾龄分段 0.返回\n");
            int sc = inputInt("请选择: ", 0, 2);
            if (sc == 0) continue;
            if (sc == 1) {
                int vals[2]; countRentersByGender(vals);   // 遍历renterHead按gender字段统计
                char gl[2][32]; strncpy(gl[0], "男性", 31); strncpy(gl[1], "女性", 31);
                drawBarChart(gl, vals, 2);
            } else {
                int vals[3]; countRentersByDrivingYears(vals);   // 驾龄分段统计：<=3 / 4-10 / >10
                char dl[3][32]; strncpy(dl[0], "0-3年", 31); strncpy(dl[1], "4-10年", 31); strncpy(dl[2], "10年+", 31);
                drawBarChart(dl, vals, 3);
            }
            pauseScreen();
        } else if (c == 4) {
            // 租车统计：按月统计(解析rentDate的月份字段，1-12月分组计数)
            int vals[12];
            countRentsByMonth(vals);   // 遍历rentHead→提取月份→对应槽位+1
            char ml[12][32];
            for (int i = 0; i < 12; i++) snprintf(ml[i], 32, "%d月", i + 1);
            drawBarChart(ml, vals, 12);
            pauseScreen();
        } else if (c == 5) { showAllInfo(); pauseScreen(); } // 直接打印
    }
}
