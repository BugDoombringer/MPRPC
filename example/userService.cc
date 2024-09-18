#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "mprpcprovider.h"

/*
UserService是一个本地服务，提供了两个本地方法，分别是Login和Register
该类定义在rpc服务提供方
*/
class UserService : public fixbug::UserServiceRpc 
{
public:
    //Login方法
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;  
        return false;
    }

    //Register方法
    bool Register(uint32_t id, std::string name, std::string pwd)
    {
        std::cout << "doing local service: Register" << std::endl;
        std::cout << "id:" << id << "name:" << name << " pwd:" << pwd << std::endl;
        return true;
    }

    
    //重写基类UserServiceRpc的虚函数Login，供mprpc框架调用
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 获取mprpc框架上报的请求参数LoginRequest
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 做本地业务Login
        bool login_result = Login(name, pwd); 

        // 把本地业务执行结果写入响应response，包括错误码、错误消息、返回值
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_sucess(login_result);

        // 将响应response序列化并通过网络发送至调用方
        done->Run();
    }

    // 步骤同上
    void Register(::google::protobuf::RpcController* controller,
                       const ::fixbug::RegisterRequest* request,
                       ::fixbug::RegisterResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();

        bool ret = Register(id, name, pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_sucess(ret);

        done->Run();
    }
};

int main(int argc, char **argv)
{
    // mprpc框架初始化
    MprpcApplication::Init(argc, argv);

    // MprpcProvider是mprpc框架中用于发布rpc服务的类
    MprpcProvider provider;

    // 将服务对象UserService和其方法Login、Register注册到服务列表provider.m_serviceMap
    provider.RegisterService(new UserService());

    // 启动rpc服务发布节点
    provider.Run();

    return 0;
}