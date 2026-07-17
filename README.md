# CarRent — 汽车租赁管理系统

基于 C++11 的命令行汽车租赁管理工具，采用单向链表管理车辆、用户和租车记录，数据通过二进制文件持久化，支持增删改查、租车退车、分类查询、分组统计、ASCII 柱状图可视化、票据打印、操作日志等完整功能。

## 技术栈

- **语言**：C++11
- **存储**：单向链表（`new`/`delete` 动态管理） + 二进制文件持久化
- **构建**：Make / CMake
- **编码**：UTF-8，中文注释与界面
- **平台**：macOS / Linux / Windows（MinGW）

## 项目结构

```
CarRent/
├── src/
│   ├── main.cpp              程序入口，include car_rent.cpp 后调用 runApp()
│   ├── car_rent.cpp           核心文件：全部常量、结构体、链表操作、工具函数、业务逻辑、主菜单
│   ├── menu1_vehicle.cpp      菜单1 — 车辆信息管理
│   ├── menu2_renter.cpp       菜单2 — 租车用户信息管理
│   ├── menu3_rent.cpp         菜单3 — 租车业务办理
│   ├── menu4_return.cpp       菜单4 — 退车业务办理
│   ├── menu5_query.cpp        菜单5 — 信息查询（分类查询 + 模糊搜索）
│   ├── menu6_statistics.cpp   菜单6 — 统计汇总 + 输出全部信息（含 ASCII 柱状图）
│   └── menu7_system.cpp       菜单7 — 系统设置（密码、报表、日志、清空数据）
├── CMakeLists.txt             CMake 构建配置
├── Makefile                   Make 构建配置
├── .clangd                    clangd 配置（让 IDE 正确分析通过 #include 引入的 .cpp 文件）
└── README.md
```

### 文件包含关系

程序通过 `#include` 直接引入 `.cpp` 文件，编译时只需编译 `main.cpp` 一个翻译单元：

```
main.cpp
  └── car_rent.cpp          ← 全部定义、全局变量、工具函数、业务函数、主菜单
        ├── menu1_vehicle.cpp
        ├── menu2_renter.cpp
        ├── menu3_rent.cpp
        ├── menu4_return.cpp
        ├── menu5_query.cpp
        ├── menu6_statistics.cpp
        └── menu7_system.cpp
```

### car_rent.cpp 内部结构（17 个部分）

| 部分    | 内容                                                                                                                                                                    |
|-------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 第一部分  | 常量定义（`constexpr`）、枚举（`VehicleStatus` / `RentStatus`）、结构体（`Vehicle` / `Renter` / `RentRecord`）、链表节点、全局变量                                                               |
| 第二部分  | 系统工具：`trimNewLine()`、`pauseScreen()`                                                                                                                                  |
| 第三部分  | 输入方法：`inputLine()`、`inputInt()`（含错误分类提示）、`inputDouble()`、`inputChar()`、`confirm()`                                                                                    |
| 第四部分  | 时间日期工具：`getNowDate()`、`getNowDateTime()`、`isLeapYear()`、`isValidDate()`、`dateToDays()`、`calcDateDiff()`                                                               |
| 第五部分  | 状态文案映射：`vehicleStatusStr()`、`rentStatusStr()`                                                                                                                         |
| 第六部分  | 结构体初始化：`initVehicle()`、`initRenter()`、`initRent()`                                                                                                                    |
| 第七部分  | 链表查找与 ID 分配：`findVehicle()`、`findRenter()`、`findRent()`、`nextVehicleId()`、`nextRenterId()`、`nextRentId()`                                                             |
| 第八部分  | 重复检查：`isPlateNoDuplicate()`、`isLicenseNoDuplicate()`、`isIdCardDuplicate()`                                                                                            |
| 第九部分  | 数据持久化：`loadVehicles()`、`saveVehicles()`、`loadRenters()`、`saveRenters()`、`loadRents()`、`saveRents()`、`loadPassword()`、`savePassword()`、`loadAllData()`、`saveAllData()` |
| 第十部分  | 密码与登录：`xorPassword()`、`checkPassword()`、`setNewPassword()`、`login()`                                                                                                  |
| 第十一部分 | 数据增删改（链表操作）：`addVehicle()`、`deleteVehicle()`、`modifyVehicle()`、`addRenter()`、`deleteRenter()`、`modifyRenter()`、`addRentRecord()`、`returnRent()`                       |
| 第十二部分 | 票据生成：`printRentTicket()`（租车票据）、`printReturnReceipt()`（退车收据）                                                                                                           |
| 第十三部分 | 输出打印（含分页）：`printVehicleHeader/Row/All()`、`printRenterHeader/Row/All()`、`printRentHeader/Row/All()`                                                                    |
| 第十四部分 | 统计与 ASCII 柱状图：各类计数函数、分组统计函数、`drawBarChart()`、`printStatistics()`                                                                                                      |
| 第十五部分 | 报表导出：`exportReport()`                                                                                                                                                 |
| 第十六部分 | `showAllInfo()` + 子模块 `#include` 引用                                                                                                                                   |
| 第十七部分 | 界面入口：`showBanner()`（含实时时钟）、`mainMenu()`、`runApp()`                                                                                                                    |

## 功能模块

### 菜单 1 — 车辆信息管理

增删改查全部车辆，字段包括车牌号、品牌、类型、颜色、购买日期、保险信息、日租金、里程。添加时自动检查车牌号重复，删除和修改通过 ID 定位链表节点。

### 菜单 2 — 租车用户信息管理

增删改查全部用户，字段包括姓名、年龄、性别、电话、驾照号、身份证号、驾龄、租车次数。添加时自动检查驾照号和身份证号重复。

### 菜单 3 — 租车业务办理

- 办理前先列出全部可用车辆（状态为"可租"），若无可用车辆则提示"没有剩余车辆"
- 输入车辆 ID 和用户 ID，录入租车日期和预计归还日期（含闰年与每月天数校验）
- 系统自动计算押金（日租金 × 3），创建租车记录并更新车辆状态为"已租"、用户租车次数 +1
- 成功后打印格式化租车票据

### 菜单 4 — 退车业务办理

- 输入租车记录 ID 和实际归还日期
- 自动计算租车天数（`calcDateDiff()`，最少 1 天），总费用 = 天数 × 日租金，退款 = 押金 − 总费用
- 更新车辆状态回"可租"，记录标记为"已归还"
- 打印格式化退车费用收据

### 菜单 5 — 信息查询

两级菜单：

- **分类查询**：
  - 车辆：按品牌 / 类型 / 颜色（`strstr` 子串匹配）/ 状态（可租/已租/维修）
  - 用户：按姓名 / 驾照号（`strstr` 子串匹配）/ 性别（大小写不敏感）
  - 租车记录：按状态（租用中/已归还）/ 日期范围（起止日期转天数值比较）
- **模糊搜索**：输入关键词，跨实体匹配车辆品牌+车牌 和 用户姓名+驾照号

### 菜单 6 — 统计汇总与输出

- **系统概览**：总数统计 + 车辆状态 ASCII 柱状图（可租/已租/维修） + 品牌分布柱状图
- **车辆统计**：按品牌 / 类型 / 颜色分组，`drawBarChart()` 绘制 `#` 柱状图
- **用户统计**：按性别 / 驾龄分段（0-3年 / 4-10年 / 10年以上）分组
- **租车统计**：按月份统计租车量
- **输出全部信息**：依次打印车辆、用户、租车记录三张表，每 20 行分页暂停

### 菜单 7 — 系统设置

- **修改密码**：验证旧密码（XOR 解密比对）→ 新密码两次输入一致 → XOR 加密后覆写 `pwd.dat`
- **导出报表**：遍历三个链表，生成带时间戳的文本文件（`report_YYYY-MM-DD_HH_MM_SS.txt`）
- **查看日志**：读取 `log.txt` 逐行输出
- **清空数据**：确认后逐个释放三个链表全部节点，计数器归零，保存空文件覆盖

## 数据模型

### Vehicle

| 字段             | 类型       | 说明               |
|----------------|----------|------------------|
| `id`           | int      | 自动递增编号           |
| `plateNo`      | char[16] | 车牌号（唯一约束）        |
| `brand`        | char[32] | 品牌               |
| `type`         | char[32] | 类型               |
| `color`        | char[16] | 颜色               |
| `purchaseDate` | char[16] | 购买日期（YYYY-MM-DD） |
| `status`       | int      | 0-可租, 1-已租, 2-维修 |
| `dailyRate`    | double   | 日租金              |
| `mileage`      | double   | 里程               |
| `insurance`    | char[64] | 保险信息             |

### Renter

| 字段             | 类型       | 说明         |
|----------------|----------|------------|
| `id`           | int      | 自动递增编号     |
| `name`         | char[32] | 姓名         |
| `age`          | int      | 年龄         |
| `gender`       | char     | 性别（M/F）    |
| `phone`        | char[20] | 联系电话       |
| `licenseNo`    | char[20] | 驾照号码（唯一约束） |
| `idCard`       | char[20] | 身份证号（唯一约束） |
| `drivingYears` | int      | 驾龄         |
| `rentCount`    | int      | 累计租车次数     |

### RentRecord

| 字段                   | 类型       | 说明           |
|----------------------|----------|--------------|
| `id`                 | int      | 自动递增编号       |
| `vehicleId`          | int      | 关联车辆编号       |
| `renterId`           | int      | 关联用户编号       |
| `rentDate`           | char[16] | 租车日期         |
| `expectedReturnDate` | char[16] | 预计归还日期       |
| `actualReturnDate`   | char[16] | 实际归还日期       |
| `deposit`            | double   | 押金（日租金 × 3）  |
| `dailyRate`          | double   | 快照日租金        |
| `totalFee`           | double   | 实际总费用        |
| `status`             | int      | 0-租用中, 1-已归还 |
| `vehicleBrand`       | char[32] | 快照车辆品牌       |
| `vehiclePlate`       | char[16] | 快照车牌号        |
| `renterName`         | char[32] | 快照用户姓名       |
| `renterLicense`      | char[20] | 快照驾照号        |

## 数据文件

| 文件            | 格式   | 说明                                        |
|---------------|------|-------------------------------------------|
| `vehicle.dat` | 二进制  | `[count:4B] [Vehicle×N]`                  |
| `renter.dat`  | 二进制  | `[count:4B] [Renter×N]`                   |
| `rent.dat`    | 二进制  | `[count:4B] [RentRecord×N]`               |
| `pwd.dat`     | 二进制  | `[username:32B] [password_encrypted:64B]` |
| `log.txt`     | 文本追加 | `YYYY-MM-DD HH:MM:SS 操作描述`                |

密码使用 XOR 0x5A 逐字节加密后存储。

## 关键算法

| 算法        | 函数                        | 实现要点                                                      |
|-----------|---------------------------|-----------------------------------------------------------|
| 日期合法性校验   | `isValidDate()`           | 长度=10、分隔符位置、数字校验、年/月/日范围、闰年 2 月 29 天                      |
| 日期转天数     | `dateToDays()`            | 从 2000-01-01 起累计全年天数 + 当月之前月份天数 + 当日                      |
| 天数差       | `calcDateDiff()`          | 两日期分别转天数后取绝对值                                             |
| 链表 ID 分配  | `nextXxxId()`             | 遍历链表取 `max(id) + 1`                                       |
| 链表添加      | `addXxx()`                | `new` 节点 → 赋值 → 找到尾节点 → 链接 → `count++` → 保存               |
| 链表删除      | `deleteXxx()`             | 遍历 → 记录前驱 → 目标节点时 `prev->next = cur->next` → `delete cur` |
| 分组统计      | `countXxxByY()`           | 遍历链表 → `strcmp` 去重 → 对应槽位 `values[found]++`               |
| ASCII 柱状图 | `drawBarChart()`          | 找最大值 → 各值 × 30 / max 决定 `#` 数量                            |
| 文件读写      | `saveXxx()` / `loadXxx()` | 先写 count，再逐节点 `fwrite`；读取时 `fread` + `new` 构建链表           |

## 代码特点

- **常量全 `constexpr`**：消除魔法数字，编译期求值
- **字符串转换用 `strtol` / `strtod`**：替代 `atoi` / `atof`，能检测转换失败
- **窄化转换用 `static_cast`**：显式声明 `size_t` → `int`、`int` → `char` 等转换
- **输入错误分类提示**：区分空输入 / 非数字 / 超出范围三种情况
- **花括号规范**：`if`/`for`/`while` 即使单条语句也用 `{}`，`case`/`default` 独占一行
- **函数单一职责**：每个函数不超过约 40 行，命名采用动宾结构
- **注释覆盖率 >10%**：每个函数前有功能描述，复杂逻辑有行内注释

## 构建与运行

### Make

```bash
make              # 编译
./CarRent         # 运行
make clean        # 清理编译产物
make distclean    # 清理编译产物 + 所有 .dat 和 log.txt
```

### CMake（CLion 推荐）

在 CLion 中直接打开项目根目录即可。终端构建：

```bash
mkdir build && cd build
cmake ..
make
./CarRent
```

### 直接 g++

```bash
g++ -std=c++11 -Wall -Wextra -o CarRent src/main.cpp
./CarRent
```

## 使用流程

1. **首次运行** → 设置用户名和密码（密码 6~16 位）
2. **登录** → 输入用户名 + 密码（最多 3 次尝试）
3. **添加车辆**（菜单 1）→ 录入车牌、品牌、类型、颜色、日期、日租金等
4. **添加用户**（菜单 2）→ 录入姓名、驾照号、身份证号等
5. **办理租车**（菜单 3）→ 选可用车辆 → 选用户 → 录入日期 → 打印票据
6. **办理退车**（菜单 4）→ 输入记录 ID 和归还日期 → 自动计费退款 → 打印收据
7. **查询**（菜单 5）→ 分类查询或模糊搜索
8. **统计**（菜单 6）→ 系统概览 / 分组统计柱状图 / 输出全部信息
9. **系统设置**（菜单 7）→ 改密码 / 导出报表 / 查看日志 / 清空数据
10. **退出** → 选 0，自动保存所有数据
