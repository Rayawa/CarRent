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
            printStatistics(); // 打印统计信息
            // 可租车辆数a，已租车辆数r，维修车辆数m=vehicleCount-a-r
            int a = countAvailableVehicles(), r = countRentedVehicles(), m = vehicleCount - a - r;
            printf("\n车辆状态:\n");
            char sl[3][32]; int sv[3];
            strncpy(sl[0], "可租", 31); strncpy(sl[1], "已租", 31); strncpy(sl[2], "维修", 31); // 参数一标签写入字符串
            sv[0] = a; sv[1] = r; sv[2] = m; // 参数二对应数值赋值
            drawBarChart(sl, sv, 3);   // 参数三一共三类，画图
            char labels[50][32]; int values[50];
            int n = countVehiclesByBrand(labels, values, 50);   // 统计函数实现参数与计算品牌数量，参数一二
            printf("\n品牌分布:\n");
            drawBarChart(labels, values, n); // 画图
            pauseScreen();
        } else if (c == 2) {
            printf("\n1.按品牌 2.按类型 3.按颜色 0.返回\n");
            int sc = inputInt("请选择: ", 0, 3);
            if (sc == 0) continue;
            char labels[50][32]; int values[50]; int n = 0;
            if (sc == 1) n = countVehiclesByBrand(labels, values, 50);   // 统计函数实现参数与计算品牌数量，参数一二
            else if (sc == 2) n = countVehiclesByType(labels, values, 50); // 统计函数实现参数与计算种类数量，参数一二
            else n = countVehiclesByColor(labels, values, 50); // 统计函数实现参数与计算颜色，参数一二
            printf("\n");
            drawBarChart(labels, values, n); // 参数三为n，画图
            pauseScreen();
        } else if (c == 3) {
            printf("\n1.按性别 2.按驾龄分段 0.返回\n");
            int sc = inputInt("请选择: ", 0, 2);
            if (sc == 0) continue;
            if (sc == 1) {
                int vals[2]; countRentersByGender(vals); // 统计函数实现参数二
                char gl[2][32]; strncpy(gl[0], "男性", 31); strncpy(gl[1], "女性", 31); // 参数一标签写入字符串
                drawBarChart(gl, vals, 2); // 参数三为两个性别，画图
            } else {
                int vals[3]; countRentersByDrivingYears(vals); // 统计函数实现参数二
                char dl[3][32]; strncpy(dl[0], "0-3年", 31); strncpy(dl[1], "4-10年", 31); strncpy(dl[2], "10年+", 31);
                drawBarChart(dl, vals, 3); // 参数三为三个段，画图
            }
            pauseScreen();
        } else if (c == 4) {
            int vals[12];
            countRentsByMonth(vals); // 统计函数实现参数二
            char ml[12][32];
            for (int i = 0; i < 12; i++) snprintf(ml[i], 32, "%d月", i + 1); // 参数一标签写入字符串
            drawBarChart(ml, vals, 12); // 参数三一共12月，画图
            pauseScreen();
        } else if (c == 5) { showAllInfo(); pauseScreen(); } // 直接打印
    }
}
