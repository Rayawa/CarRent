/*
 * 汽车租赁管理系统
 * 文件: menu2_renter.cpp
 * 功能: 租车用户信息管理子菜单
 * 日期: 2026-07
 */
void menu2Renter() {
    while (true) {
        printf("\n1.添加用户 2.删除用户 3.修改用户 4.显示所有 0.返回\n");
        int c = inputInt("请选择: ", 0, 4);
        if (c == 0) return;
        if (c == 4) { printAllRenters(); pauseScreen(); continue; }
        if (c == 1) {
            // 添加用户：初始化结构体→逐字段录入→驾照号+身份证重复检查→创建链表节点→保存
            Renter r;
            initRenter(r);
            inputLine("姓名: ", r.name, MAX_NAME_LEN);
            r.age = inputInt("年龄: ", 1, 120);
            r.gender = inputChar("性别(M/F): ", "MmFf");
            if (r.gender == 'm') r.gender = 'M';   // 统一转大写
            if (r.gender == 'f') r.gender = 'F';
            inputLine("电话: ", r.phone, MAX_PHONE_LEN);
            while (true) {
                inputLine("驾照号: ", r.licenseNo, MAX_LICENSE_LEN);
                if (!isLicenseNoDuplicate(r.licenseNo)) break;   // 遍历链表检查驾照号唯一性
                printf("驾照号已存在，请重新输入\n");
            }
            while (true) {
                inputLine("身份证号: ", r.idCard, MAX_IDCARD_LEN);
                if (!isIdCardDuplicate(r.idCard)) break;         // 遍历链表检查身份证号唯一性
                printf("身份证号已存在，请重新输入\n");
            }
            r.drivingYears = inputInt("驾龄: ", 0, 60);
            addRenter(r);   // 分配ID→创建节点→链到末尾→计数+1→保存文件→写日志
            printf("已添加\n");
            pauseScreen();
        } else if (c == 2) {
            // 删除用户：展示全部→输入ID→链表查找→前驱重连→释放内存
            printAllRenters();
            int id = inputInt("输入用户ID: ", 1, 9999);
            printf(deleteRenter(id) ? "已删除\n" : "没找到\n");
            pauseScreen();
        } else if (c == 3) {
            // 修改用户：输入ID→findRenter遍历链表定位→展示当前值→逐字段覆盖→保存
            int id = inputInt("输入用户ID: ", 1, 9999);
            Renter* p = findRenter(id);
            if (!p) { printf("没找到\n"); pauseScreen(); continue; }
            Renter r = *p;
            inputLine("姓名: ", r.name, MAX_NAME_LEN);
            r.age = inputInt("年龄: ", 1, 120);
            r.gender = inputChar("性别(M/F): ", "MmFf");
            if (r.gender == 'm') r.gender = 'M';
            if (r.gender == 'f') r.gender = 'F';
            inputLine("电话: ", r.phone, MAX_PHONE_LEN);
            inputLine("驾照号: ", r.licenseNo, MAX_LICENSE_LEN);
            inputLine("身份证号: ", r.idCard, MAX_IDCARD_LEN);
            r.drivingYears = inputInt("驾龄: ", 0, 60);
            printf(modifyRenter(id, r) ? "已修改\n" : "失败\n");
            pauseScreen();
        }
    }
}
