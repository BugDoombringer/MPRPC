#pragma once

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

/*
MprpcChannel 类继承自 google::protobuf::RpcChannel，
是 RPC 框架中用于发送请求的通信通道，
它的作用是通过网络发送请求消息并接收响应。
*/
class MprpcChannel : public google::protobuf::RpcChannel
{
public:
    // 重写 CallMethod 函数，用于发起 RPC 方法调用
    // 主要完成数据序列化和网络发送
    void CallMethod(const google::protobuf::MethodDescriptor *method,
                    google::protobuf::RpcController *controller,
                    const google::protobuf::Message *request,
                    google::protobuf::Message *response,
                    google::protobuf::Closure *done);
};