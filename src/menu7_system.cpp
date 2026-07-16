/*
 * 汽车租赁管理系统
 * 文件: menu7_system.cpp
 * 功能: 系统设置子菜单
 * 日期: 2026-07
 */
void menu7System() {
    while (true) {
        printf("\n1.修改密码 2.导出报表 3.查看日志 4.清空数据 0.返回\n");
        int c = inputInt("请选择: ", 0, 4);
        if (c == 0) return;
        if (c == 1) {
            // 修改密码：验证旧密码(XOR解密比对)→新密码两次输入一致→XOR加密后覆写存储
            char oldPwd[64], newPwd[64], confirmPwd[64];
            inputLine("旧密码: ", oldPwd, sizeof(oldPwd));
            inputLine("新密码: ", newPwd, sizeof(newPwd));
            inputLine("确认密码: ", confirmPwd, sizeof(confirmPwd));
            if (strcmp(newPwd, confirmPwd) != 0 || !checkPassword(oldPwd)) {   // 新密码不一致或旧密码错误
                printf("失败\n");
            } else {
                setNewPassword(newPwd);   // XOR加密→存入passwordStore→写pwd.dat
                printf("已修改\n");
            }
            pauseScreen();
        } else if (c == 2) {
            // 导出报表：遍历三个链表写文本文件(含时间戳文件名)
            exportReport();
            printf("已导出\n");
            pauseScreen();
        } else if (c == 3) {
            // 查看日志：打开log.txt逐行读取输出
            FILE* fp = fopen(FILE_LOG, "r");
            if (!fp) { printf("暂无日志\n"); pauseScreen(); continue; }
            char line[256];
            while (fgets(line, sizeof(line), fp)) printf("%s", line);   // 逐行输出，保留原格式
            fclose(fp);
            pauseScreen();
        } else if (c == 4) {
            // 清空数据：确认后→逐个释放三个链表所有节点→计数器归零→保存覆盖文件
            if (confirm("确认清空数据?")) {
                while (vehicleHead) { VehicleNode* t = vehicleHead; vehicleHead = vehicleHead->next; delete t; }
                while (renterHead)   { RenterNode*   t = renterHead;   renterHead = renterHead->next;   delete t; }
                while (rentHead)     { RentNode*     t = rentHead;     rentHead = rentHead->next;       delete t; }
                vehicleCount = renterCount = rentCount = 0;
                saveAllData();   // 写空数据到三个.dat文件
                printf("已清空\n");
            }
            pauseScreen();
        }
    }
}
