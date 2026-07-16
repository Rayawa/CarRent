/*
 * 汽车租赁管理系统
 * 文件: menu8_system.cpp  功能: 系统设置子菜单
 * 作者: 孙老师组     日期: 2026-07
 */
//==========================菜单8：系统设置====================
// 修改密码/导出报表/查看日志/清空数据
void menu8System() {
    while (true) {
        printf("\n1.修改密码 2.导出报表 3.查看日志 4.清空数据 0.返回\n");
        int c = inputInt("请选择: ", 0, 4);
        if (c == 0) return;
        // 修改密码：验证旧密码后设置新密码
        if (c == 1) {
            char oldPwd[64], newPwd[64], confirmPwd[64];
            inputLine("旧密码: ", oldPwd, sizeof(oldPwd));
            inputLine("新密码: ", newPwd, sizeof(newPwd));
            inputLine("确认密码: ", confirmPwd, sizeof(confirmPwd));
            if (strcmp(newPwd, confirmPwd) != 0 || !checkPassword(oldPwd)) {
                printf("失败\n");
            } else {
                setNewPassword(newPwd);
                printf("已修改\n");
            }
            pauseScreen();
        // 导出报表：生成带时间戳的文本报表文件
        } else if (c == 2) {
            exportReport();
            printf("已导出\n");
            pauseScreen();
        // 查看日志：打开日志文件并逐行输出
        } else if (c == 3) {
            FILE* fp = fopen(FILE_LOG, "r");
            if (!fp) { printf("暂无日志\n"); pauseScreen(); continue; }
            char line[256];
            while (fgets(line, sizeof(line), fp)) printf("%s", line);
            fclose(fp);
            pauseScreen();
        // 清空数据：将所有计数器归零后保存
        } else if (c == 4) {
            if (confirm("确认清空数据?")) {
                while (vehicleHead) { VehicleNode* t = vehicleHead; vehicleHead = vehicleHead->next; delete t; }
                while (renterHead) { RenterNode* t = renterHead; renterHead = renterHead->next; delete t; }
                while (rentHead) { RentNode* t = rentHead; rentHead = rentHead->next; delete t; }
                vehicleCount = renterCount = rentCount = 0;
                saveAllData();
                printf("已清空\n");
            }
            pauseScreen();
        }
    }
}
