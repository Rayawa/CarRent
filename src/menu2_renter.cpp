/*
 * 汽车租赁管理系统
 * 文件: menu2_renter.cpp
 * 功能: 租车用户信息管理子菜单
 * 日期: 2026-07-16
 */
void menu2Renter() {
    while (true) {
        printf("\n1.添加用户 2.删除用户 3.修改用户 4.显示所有 0.返回\n");
        int c = inputInt("请选择: ", 0, 4);
        if (c == 0) return;
        if (c == 4) { printAllRenters(); pauseScreen(); continue; }
        if (c == 1) {
            Renter r;
            initRenter(r);
            inputLine("姓名: ", r.name, MAX_NAME_LEN);
            r.age = inputInt("年龄: ", 1, 120);
            r.gender = inputChar("性别(M/F): ", "MmFf");
            if (r.gender == 'm') r.gender = 'M';
            if (r.gender == 'f') r.gender = 'F';
            inputLine("电话: ", r.phone, MAX_PHONE_LEN);
            while (true) {
                inputLine("驾照号: ", r.licenseNo, MAX_LICENSE_LEN);
                if (!isLicenseNoDuplicate(r.licenseNo)) break;
                printf("驾照号已存在，请重新输入\n");
            }
            while (true) {
                inputLine("身份证号: ", r.idCard, MAX_IDCARD_LEN);
                if (!isIdCardDuplicate(r.idCard)) break;
                printf("身份证号已存在，请重新输入\n");
            }
            r.drivingYears = inputInt("驾龄: ", 0, 60);
            addRenter(r); // 输入r的所有信息（部分校验）并进入函数添加
            printf("已添加\n");
            pauseScreen();
        } else if (c == 2) {
            printAllRenters();
            int id = inputInt("输入用户ID: ", 1, 9999);
            printf(deleteRenter(id) ? "已删除\n" : "没找到\n"); // 删除对应的id，如果返回false说明没找到
            pauseScreen();
        } else if (c == 3) {
            int id = inputInt("输入用户ID: ", 1, 9999);
            Renter* p = findRenter(id);
            if (!p) { printf("没找到\n"); pauseScreen(); continue; } // 判断到底有没有这个用户
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
            printf(modifyRenter(id, r) ? "已修改\n" : "失败\n"); // 输入所有信息并替换r的所有信息（部分校验）并进入函数添加，如果返回false说明失败了
            pauseScreen();
        }
    }
}
