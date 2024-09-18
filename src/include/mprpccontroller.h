#pragma once
#include <google/protobuf/service.h>
#include <string>

// 用于控制和管理 RPC 方法的调用过程
class MprpcController : public google::protobuf::RpcController
{
public:
    MprpcController();

    // 重置控制器的状态和错误信息
    void Reset();

    // 判断 RPC 方法是否执行失败
    bool Failed() const;

    // 返回 RPC 方法执行失败时的错误信息
    std::string ErrorText() const;

    // 设置执行失败状态，并指定失败的原因（错误信息）
    void SetFailed(const std::string &reason);

    // 目前未实现具体的功能
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure *callback);

private:
    bool m_failed;         // RPC方法执行过程中的状态
    std::string m_errText; // RPC方法执行过程中的 错误信息
};