#pragma once

#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>

// zk客户端类
class ZkClient
{
public:
    ZkClient();
    ~ZkClient();
    // zkclient启动连接zkserver
    void Start();
    // 在zkserver上根据指定的path创建znode节点
    void Create(const char *path, const char *data, int datalen, int state = 0);
    // 根据指定的znode路径path，获取znode节点的值
    std::string GetData(const char *path);

private:
    // zk客户端句柄
    zhandle_t *m_zhandle;
};