
# QQchat即时聊天系统

基于MFC框架开发的局域网即时通讯工具，支持用户管理、多人聊天、聊天记录等功能。


## 项目概述
- **项目名称**：QQchat即时聊天系统
- **开发成员**：笙酒
- **技术栈**：C++/MFC、Windows Socket、Visual Studio 2022


## 功能特性
1. **用户管理**：
   - 注册/登录验证
   - 头像更换与个人信息修改
   - 在线用户实时列表

2. **聊天功能**：
   - 单聊与群聊支持（最多6人）
   - 消息内容包含时间戳与用户名
   - 窗口抖动特效

3. **辅助功能**：
   - 聊天记录本地存储
   - 系统托盘最小化
   - 自动登录配置


## 安装与运行
### 环境要求
- Windows 10/11
- Visual Studio 2022（含MFC组件）

### 配置步骤
1. **服务器端**：
   - 编译 `Server` 项目
   - 启动后设置监听端口（默认6600）

2. **客户端**：
   - 编译 `Client` 项目
   - 登录界面配置服务器IP（默认127.0.0.1）与端口


## 使用指南
### 基础操作
1. **注册账号**：
   - 输入用户名与密码完成注册
   - 支持密码找回功能

2. **聊天界面**：
   - 双击好友列表打开聊天窗口
   - 输入消息后按回车或点击发送
   - 支持表情符号与文件传输

### 高级功能
- **头像设置**：右键点击头像选择更换
- **聊天记录**：主界面右键查看历史消息
- **系统通知**：服务器端实时显示用户上下线状态


## 项目结构
```
QQchat/
├── Server/           # 服务器端代码
│   ├── Socket.cpp    # 网络通信逻辑
│   └── ServerDlg.cpp # 服务器界面
├── Client/           # 客户端代码
│   ├── ChatDlg.cpp   # 聊天窗口实现
│   ├── FriDlg.cpp    # 好友列表管理
│   └── OpenQQDlg.cpp # 主界面逻辑
└── Docs/             # 实训文档与设计图
```


## 实训总结
通过本项目的开发，团队成员掌握了以下技能：
1. MFC框架下的GUI程序开发
2. Windows Socket网络通信编程
3. 多线程与消息机制处理
4. 团队协作与项目管理流程

项目实现过程中遇到的挑战包括：
- 网络通信的稳定性优化
- 多窗口同步显示问题
- 跨平台兼容性处理


## 联系方式
如有问题或建议，欢迎通过以下方式联系：
- 邮箱：752501297@qq.com
- 网站：www.lhxloveljh.com

**注**：本项目为教学实训作品，部分功能仍在持续优化中。
