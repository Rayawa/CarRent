# 全部需求补全计划（极简版）

## 原则
- 代码量最小化，拒绝花哨
- 新手友好，逻辑直白
- 保持现有 `#include "xxx.cpp"` 架构

---

## Phase 1：代码规范

### 1.1 文件头部注释（10个文件）
每个 `.cpp` 顶部加 5 行标准头：
```cpp
/*
 * 汽车租赁管理系统
 * 文件: xxx.cpp  功能: 车辆信息管理
 * 作者: [姓名]   日期: 2026-07
 */
```

### 1.2 函数文档注释
car_rent.cpp 中每个函数前加一行注释：`// 功能: xxx, 入参: xxx, 返回: xxx`

### 1.3 命名修正
| 旧名          | 新名             |
|-------------|----------------|
| isLeap      | isLeapYear     |
| validDate   | isValidDate    |
| diffDays    | calcDateDiff   |
| trimNewline | trimNewLine    |
| nowDate     | getNowDate     |
| nowDateTime | getNowDateTime |

---

## Phase 2：票据生成

在 `car_rent.cpp` 新增 2 个函数（共 ~60 行）：

```
printRentTicket(RentRecord& r)
  输出: ===== 汽车租赁公司租车票据 =====
        车辆: xxx  车牌: xxx  日租金: xxx
        用户: xxx  驾照: xxx
        租车日期: xxx → 预计归还: xxx
        押金: xxx

printReturnReceipt(RentRecord& r, int days, double total, double refund)
  输出: ===== 汽车租赁公司租车费用收据 =====
        租车天数: xxx  日租金: xxx
        总费用: xxx  押金: xxx  退款: xxx
```

在 `menu3Rent()` 和 `menu4Return()` 中成功后调用。

---

## Phase 3：用户名登录

在 car_rent.cpp 中：
- 新增 `char username[32]` + `loadUsername/saveUsername`（~20行）
- 修改 `login()`：先输入用户名 → 再输入密码
- 首次使用时同时设置用户名和密码
- `pwd.dat` 格式改为：`[username 32B][password 64B]`

---

## Phase 4：分类查询

重写 `menu5_query.cpp`（~100行），结构：
```
1. 车辆查询 → 2级菜单: 按品牌/类型/颜色/状态
2. 用户查询 → 2级菜单: 按姓名/驾照号/性别
3. 租车查询 → 2级菜单: 按状态/日期范围
```
每种查询：遍历数组 → if 条件匹配 → printRow

---

## Phase 5：分组统计

新增统计函数（~80行）：
```
countByBrand()      → 去重计数，输出 "丰田:3 本田:2"
countByType()       → 同上
countByColor()      → 同上
countByGender()     → 同上
countByDrivingYrs() → 分段: 0-3年/4-10年/10年+
countByMonth()      → 按月统计租车量
```
重写 `menu6Statistics()` 展示以上结果。

---

## Phase 6：链表（替换数组）

策略：车辆/用户/租车记录 三个模块全部使用链表。

新增 `linked_list.h`（用 `#include` 引入，~100行）：
```cpp
// 通用链表节点
template<typename T>
struct Node { T data; Node* next; };

// 基本操作（非模板，每个类型写一套）
// 车辆链表: VehicleNode, insertVehicle, deleteVehicleById, findVehicleById, saveVehiclesToList, loadVehiclesFromList
// 用户链表: 同上
// 记录链表: 同上
```

修改 car_rent.cpp：
- 删除 `Vehicle vehicles[MAX_VEHICLES]` 等全局数组
- 改为 `VehicleNode* vehicleHead = nullptr` 指针
- 所有遍历 `vehicles[i]` → 链表 while 循环
- save/load 改为逐节点读写

---

## Phase 7：扩展功能

### 7.1 实时时钟（~3行）
`showBanner()` 中调用 `getNowDateTime()` 打印当前时间。

### 7.2 进度条（~15行）
`showProgressBar(const char* msg, int cur, int total)` — 用 `\r` 刷新一行 `[####    ]`。

### 7.3 ASCII 柱状图（~20行）
`drawBarChart(const char* label[], int values[], int n)` — 用 `#` 画柱。

### 7.4 分页（~15行）
`printAllXxx` 每 20 行暂停一次。

### 7.5 重复检查（~30行）
`isPlateNoDuplicate(plateNo)` 等 3 个函数，`addVehicle/addRenter` 中调用。

### 7.6 错误分类（~10行）
`inputInt` 返回时区分：空输入 / 非数字 / 超出范围，分别提示。

---

## 实施顺序

| 顺序     | 阶段    | 预估新增行    |
|--------|-------|----------|
| 1      | 代码规范  | ~160     |
| 2      | 票据生成  | ~60      |
| 3      | 用户名登录 | ~30      |
| 4      | 分类查询  | ~100     |
| 5      | 分组统计  | ~80      |
| 6      | 链表    | ~350     |
| 7      | 扩展功能  | ~100     |
| **合计** |       | **~880** |
