# 通讯录管理系统（版本1.11）
# Contact Management System (Version 1.11)

## 项目简介
## Project Introduction

这是一个基于MFC（Microsoft Foundation Classes）开发的Windows桌面通讯录管理系统，提供了完整的联系人信息管理功能，包括添加、查看、修改、删除联系人等操作，并支持数据持久化存储。

This is a Windows desktop contact management system developed based on MFC (Microsoft Foundation Classes). It provides complete contact information management functions, including adding, viewing, modifying, deleting contacts, etc., and supports data persistence storage.

## 功能特点
## Features

### 1. 用户安全验证
### 1. User Security Verification
- 登录密码保护机制
- Login password protection mechanism
- 安全协议确认
- Security agreement confirmation
- 密码管理功能
- Password management function

### 2. 联系人管理
### 2. Contact Management
- **添加联系人**：录入姓名、电话号码、性别、年龄和地址信息
- **Add Contact**: Enter name, phone number, gender, age and address information
- **查看联系人**：列表展示所有联系人基本信息
- **View Contacts**: List display of basic information of all contacts
- **详细信息**：查看、修改或删除联系人的详细信息
- **Detailed Information**: View, modify or delete detailed information of contacts
- **数据验证**：防止添加重复联系人
- **Data Validation**: Prevent adding duplicate contacts
- **批量操作**：支持清空所有联系人
- **Batch Operations**: Support clearing all contacts

### 3. 数据持久化
### 3. Data Persistence
- 自动保存联系人信息到文件
- Automatically save contact information to files
- 程序启动时自动加载已保存的联系人数据
- Automatically load saved contact data when the program starts
- 使用文本文件格式存储，便于备份和迁移
- Use text file format for storage, easy to backup and migrate

## 技术架构
## Technical Architecture

### 核心数据结构
### Core Data Structure

```cpp
// 联系人基本信息类
typedef struct contact {
    string name;       // 姓名
    string phonenumber;// 电话号码
    int age;           // 年龄
    string sex;        // 性别
    string address;    // 地址
    // 其他成员函数...
} contact;

// 联系人列表管理类
class ContactList {
    // 成员变量和函数
    contact Person[1000];  // 最多存储1000个联系人
    // 其他成员函数...
};
```

### 主要模块
### Main Modules

| 模块 | 主要职责 | 文件位置 | <mcfile>引用 |
|------|---------|---------|-------------|
| 登录模块 | 用户验证和安全协议 | MFCApplication1Dlg.cpp | <mcfile name="MFCApplication1Dlg.cpp" path="f:\Projects\VS_C++Project\通讯录1.1源文件\MFCApplication1Dlg.cpp"></mcfile> |
| 联系人数据结构 | 定义联系人及列表管理 | contact.h | <mcfile name="contact.h" path="f:\Projects\VS_C++Project\通讯录1.1源文件\contact.h"></mcfile> |
| 主菜单界面 | 联系人列表展示与管理 | MENU.cpp | <mcfile name="MENU.cpp" path="f:\Projects\VS_C++Project\通讯录1.1源文件\MENU.cpp"></mcfile> |
| 添加联系人 | 新建联系人信息录入 | DIALOG_ADD.cpp | <mcfile name="DIALOG_ADD.cpp" path="f:\Projects\VS_C++Project\通讯录1.1源文件\DIALOG_ADD.cpp"></mcfile> |
| 联系人详情 | 查看、修改、删除联系人 | DIALOG_DETAIL.cpp | <mcfile name="DIALOG_DETAIL.cpp" path="f:\Projects\VS_C++Project\通讯录1.1源文件\DIALOG_DETAIL.cpp"></mcfile> |

| Module | Main Responsibility | File Location | <mcfile> Reference |
|--------|---------------------|---------------|-------------------|
| Login Module | User verification and security agreement | MFCApplication1Dlg.cpp | <mcfile name="MFCApplication1Dlg.cpp" path="f:\Projects\VS_C++Project\通讯录1.1源文件\MFCApplication1Dlg.cpp"></mcfile> |
| Contact Data Structure | Define contact and list management | contact.h | <mcfile name="contact.h" path="f:\Projects\VS_C++Project\通讯录1.1源文件\contact.h"></mcfile> |
| Main Menu Interface | Contact list display and management | MENU.cpp | <mcfile name="MENU.cpp" path="f:\Projects\VS_C++Project\通讯录1.1源文件\MENU.cpp"></mcfile> |
| Add Contact | New contact information entry | DIALOG_ADD.cpp | <mcfile name="DIALOG_ADD.cpp" path="f:\Projects\VS_C++Project\通讯录1.1源文件\DIALOG_ADD.cpp"></mcfile> |
| Contact Detail | View, modify, delete contacts | DIALOG_DETAIL.cpp | <mcfile name="DIALOG_DETAIL.cpp" path="f:\Projects\VS_C++Project\通讯录1.1源文件\DIALOG_DETAIL.cpp"></mcfile> |

### 数据存储
### Data Storage

- 联系人数据存储在项目根目录下的`contact.txt`文件中
- Contact data is stored in the `contact.txt` file in the project root directory
- 每行存储一个联系人信息，格式为：姓名\t电话\t性别\t年龄\t地址
- Each line stores contact information in the format: Name\tPhone\tGender\tAge\tAddress
- 使用文件读写操作实现数据持久化
- Use file read and write operations to achieve data persistence

## 安装与运行
## Installation and Operation

### 系统要求
### System Requirements
- Windows操作系统
- Windows operating system
- Visual Studio 2017或更高版本（用于编译）
- Visual Studio 2017 or higher (for compilation)
- MFC库支持
- MFC library support

### 编译运行
### Compilation and Operation
1. 使用Visual Studio打开项目文件`通讯录1.11.sln`
1. Open the project file `通讯录1.11.sln` with Visual Studio
2. 选择编译配置（Debug或Release）
2. Select the compilation configuration (Debug or Release)
3. 点击"生成" -> "生成解决方案"进行编译
3. Click "Build" -> "Build Solution" to compile
4. 编译完成后，可以在Debug或Release目录下找到可执行文件
4. After compilation is complete, the executable file can be found in the Debug or Release directory

### 直接运行
### Direct Operation
- 可以直接运行Debug目录下的`通讯录1.11.exe`文件
- You can directly run the `通讯录1.11.exe` file in the Debug directory

## 使用指南
## User Guide

### 登录流程
### Login Process
1. 启动程序，进入登录界面
1. Start the program and enter the login interface
2. 阅读并勾选"安全协议"选项
2. Read and check the "Security Agreement" option
3. 输入正确的密码，点击"登录"按钮或按回车键
3. Enter the correct password and click the "Login" button or press Enter

### 主界面操作
### Main Interface Operations
- **添加联系人**：点击"添加"按钮，在弹出的对话框中填写联系人信息
- **Add Contact**: Click the "Add" button and fill in the contact information in the pop-up dialog box
- **查看/修改/删除**：在列表中选择联系人，点击"详细"按钮进行操作
- **View/Modify/Delete**: Select a contact in the list and click the "Detail" button to operate
- **保存退出**：点击"保存"按钮将数据保存并退出程序
- **Save and Exit**: Click the "Save" button to save the data and exit the program
- **清空联系人**：点击"清空"按钮删除所有联系人（此操作不可恢复）
- **Clear Contacts**: Click the "Clear" button to delete all contacts (this operation cannot be recovered)
- **密码管理**：点击"密码"按钮可以修改登录密码
- **Password Management**: Click the "Password" button to modify the login password

### 数据录入规则
### Data Entry Rules
- 姓名和电话号码为必填项
- Name and phone number are required fields
- 年龄为整数
- Age must be an integer
- 性别和地址为选填项
- Gender and address are optional fields
- 系统会自动检测并提示重复联系人
- The system will automatically detect and prompt duplicate contacts

## 开发说明
## Development Instructions

### 项目结构
### Project Structure
```
├── contact.h          # 联系人数据结构定义
├── MFCApplication1Dlg.cpp # 登录界面实现
├── MENU.cpp           # 主菜单界面实现
├── DIALOG_ADD.cpp     # 添加联系人对话框实现
├── DIALOG_DETAIL.cpp  # 联系人详情对话框实现
├── DIALOG_CODE.cpp    # 密码管理对话框实现
└── contact.txt        # 联系人数据存储文件
```

### 核心功能实现
### Core Function Implementation

1. **联系人数据管理**
1. **Contact Data Management**

```cpp
// 添加联系人
void ContactList::input(contact temp) {
    Person[line()] = temp;
}

// 保存联系人到文件
void ContactList::SaveContact() {
    // 文件操作实现
}

// 从文件加载联系人
void ContactList::ReadContact() {
    // 文件操作实现
}
```

2. **用户界面交互**
2. **User Interface Interaction**

```cpp
// 主菜单联系人列表显示
void ContactList::OutputList(CListCtrl& m_List, CStatic &Number) {
    // 列表控件操作实现
}
```

## 注意事项
## Notes

1. 程序使用简单的文本文件存储数据，请定期备份`contact.txt`文件以防数据丢失
1. The program uses simple text files to store data, please back up the `contact.txt` file regularly to prevent data loss
2. 密码保存在系统中，请妥善保管
2. The password is stored in the system, please keep it properly
3. 程序最大支持存储1000个联系人
3. The program supports storing up to 1000 contacts
4. 清空操作会删除所有联系人数据，请谨慎使用
4. The clear operation will delete all contact data, please use it with caution

## 版本历史
## Version History
- v1.11：当前版本，优化了界面交互体验
- v1.11: Current version, optimized interface interaction experience
- v1.10：修复了已知bug，增强了数据安全性
- v1.10: Fixed known bugs and enhanced data security

## 开发者信息
## Developer Information

本项目由MFC框架开发，适用于Windows平台的通讯录管理应用。

This project is developed with MFC framework and is suitable for contact management applications on Windows platform.

---

## 版权信息
## Copyright Information

© 2023 通讯录管理系统 版权所有
© 2023 Contact Management System. All Rights Reserved.