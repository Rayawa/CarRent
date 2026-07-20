/*
 * 汽车租赁管理系统
 * 文件: menu7_system.cpp
 * 功能: 系统设置子菜单
 * 日期: 2026-07-16
 */
void menu7System() {
    while (true) {
        printf("\n1.修改密码 2.导出报表 3.查看日志 4.清空数据 0.返回\n");
        int c = inputInt("请选择: ", 0, 4);
        if (c == 0) return;
        if (c == 1) {
            char oldPwd[64], newPwd[64], confirmPwd[64]; // 定义三种密码并输入
            inputLine("旧密码: ", oldPwd, sizeof(oldPwd));
            inputLine("新密码: ", newPwd, sizeof(newPwd));
            inputLine("确认密码: ", confirmPwd, sizeof(confirmPwd));
            if (strcmp(newPwd, confirmPwd) != 0 || !checkPassword(oldPwd)) {
                printf("失败\n"); // 新旧不一致 || 与旧密码不相同
            } else {
                setNewPassword(newPwd); // 设置新密码
                printf("已修改\n");
            }
            pauseScreen();
        } else if (c == 2) {
            exportReport(); // 导出报表
            printf("已导出\n");
            pauseScreen();
        } else if (c == 3) {
            FILE* fp = fopen(FILE_LOG, "r"); // 打开日志
            if (!fp) { printf("暂无日志\n"); pauseScreen(); continue; } // 错误处理
            char line[256];
            while (fgets(line, sizeof(line), fp)) printf("%s", line); // 逐行输出
            fclose(fp); // 关闭文件
            pauseScreen();
        } else if (c == 4) {
            if (confirm("确认清空数据?")) { // 全部链表清空
                while (vehicleHead) { VehicleNode* t = vehicleHead; vehicleHead = vehicleHead->next; delete t; }
                while (renterHead)   { RenterNode*   t = renterHead;   renterHead = renterHead->next;   delete t; }
                while (rentHead)     { RentNode*     t = rentHead;     rentHead = rentHead->next;       delete t; }
                vehicleCount = renterCount = rentCount = 0; // 三种数据数量清空
                saveAllData();
                printf("已清空\n");
            }
            pauseScreen();
        }
    }
}
