#pragma once

#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

// 负责框架的初始化操作，eg. 解析加载配置文件
class MprpcApplication
{
public:
    // 初始化框架，解析加载配置文件
    static void Init(int argc, char **argv);

    // 获取MprpcApplication单例
    static MprpcApplication &GetInstance();

    // 获取配置文件信息
    static MprpcConfig &GetConfig();

private:
    // 存储配置文件信息
    static MprpcConfig m_config;

    MprpcApplication() {}
    MprpcApplication(const MprpcApplication &) = delete;
    MprpcApplication(MprpcApplication &&) = delete;
};