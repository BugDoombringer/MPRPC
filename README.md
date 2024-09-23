#项目名称
基于Muduo和Protobuf的分布式RPC通信框架

#项目介绍
该项目开发的RPC框架可以实现分布式系统中各节点的高效通信，基于Muduo网络库来处理高并发的TCP网络连接，基于Protobuf进行数据序列化和反序列化，以便高效传输结构化的数据，并且使用了ZooKeeper中的服务发现技术，以便服务调用方可以动态地查询可用的服务。

#功能模块
1. RPC服务提供模块：存储要提供的RPC服务和方法的所有信息，并且内嵌Muduo网络模块，定义了连接回调和读写事件回调函数，在 读写回调函数中处理远程调用请求并返回响应。
2. RPC服务调用模块：负责构建调用请求并发送至服务提供方，然后接收响应。
3. ZooKeeper客户端模块：封装了ZooKeeper的接口，如连接ZooKeeper，创建节点等。
4. 日志模块：将产生的日志信息存入栈空间的缓冲队列，由单独的线程异步写入磁盘文件。
5. 框架初始化、配置文件加载模块。

#项目特点
1. 基于Muduo网络库实现高并发的RPC同步调用请求处理。
2. 使用Protobuf作为RPC方法调用和参数的序列化和反序列化。
3. 基于线程安全的缓冲队列实现异步日志输出。
4. 使用ZooKeeper作为服务治理中间件，提供服务注册和服务发现功能。

#开发环境
操作系统：Ubuntu 20.04
依赖库：Muduo、Protobuf、ZooKeeper、CMake

#构建项目
1. 克隆代码仓库
git clone git@github.com:BugDoombringer/MPRPC.git
cd MPRPC
2. 安装依赖库
确保系统已安装依赖库
3. 编译项目
./autobuild.sh

#运行案例
1. 服务提供方
cd bin/
./provider -i test.conf
2. 服务调用方
./consumer -i test.conf
test.conf为配置文件，根据自己服务器情况修改

#贡献
如果你有兴趣贡献代码，欢迎提交 Pull Request，或通过 Issue 反馈建议与问题。

#许可证
该项目遵循 MIT 开源许可证。
