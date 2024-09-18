#include "zookeeperutil.h"
#include "mprpcapplication.h"
#include <semaphore.h>
#include <iostream>

// ZooKeeper 客户端的回调函数，
// 用于处理会话相关的事件，当客户端接收到事件时，这个函数会被调用
void global_watcher(zhandle_t *zh, int type,
                   int state, const char *path, void *watcherCtx)
{
    if (type == ZOO_SESSION_EVENT)  // 回调的消息类型是和会话相关的消息类型
	{
		if (state == ZOO_CONNECTED_STATE)  // zkclient和zkserver连接成功
		{
			sem_t *sem = (sem_t*)zoo_get_context(zh);

			// 加此判断是为了防止zoo_get_context先于zoo_set_context执行
			if (sem)
			{
				sem_post(sem);
			}
			else
			{
				std::cerr << "Failed to get ZooKeeper context." << std::endl;
				// 处理错误或采取适当的行动
			}
		}
	}
}

ZkClient::ZkClient() : m_zhandle(nullptr)
{
}

ZkClient::~ZkClient()
{
    if (m_zhandle != nullptr)
    {
        zookeeper_close(m_zhandle); // 关闭句柄，释放资源
    }
}

// 连接zkserver
void ZkClient::Start()
{
    std::string host = MprpcApplication::GetInstance().GetConfig().Load("zookeeperip");
    std::string port = MprpcApplication::GetInstance().GetConfig().Load("zookeeperport");
    std::string connstr = host + ":" + port;

	// 初始化 ZooKeeper 客户端，会创建一个与 ZooKeeper 服务器的连接。
	// 参数：
	//   connstr.c_str()：ZooKeeper 服务器连接字符串，格式为 "hostname:port"。
	//   global_watcher：回调函数，当接收到 ZooKeeper 事件时，会调用该函数。
	//   30000：会话超时时间，单位为毫秒，设置为 30 秒。
	//   nullptr：此处为 clientid，传递 nullptr 表示不指定初始客户端 ID，ZooKeeper 将生成新的客户端 ID。
	//   nullptr：用户上下文，传递给 watcher 函数的自定义上下文，当前设置为 nullptr。
	//   0：标志位，当前设置为 0 表示没有特殊标志。
	m_zhandle = zookeeper_init(connstr.c_str(), global_watcher, 30000, nullptr, nullptr, 0);
    if (nullptr == m_zhandle) 
    {
        std::cout << "zookeeper_init error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    sem_t sem;
    sem_init(&sem, 0, 0);
    zoo_set_context(m_zhandle, &sem);

	// 等待zkclient连接zkserver成功
    sem_wait(&sem);
    std::cout << "zookeeper_init success!" << std::endl;
}

void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
    char path_buffer[128];
    int bufferlen = sizeof(path_buffer);
    int flag;
	// 先判断path表示的znode节点是否存在，如果存在，就不再重复创建
	flag = zoo_exists(m_zhandle, path, 0, nullptr);
	if (ZNONODE == flag) // 表示path的znode节点不存在
	{
		// 创建指定path的znode节点
		flag = zoo_create(m_zhandle, path, data, datalen,
						  &ZOO_OPEN_ACL_UNSAFE, state, path_buffer, bufferlen); // 这里path_buffer, bufferlen没有用到，可以传空
		if (flag == ZOK)
		{
			std::cout << "znode create success... path:" << path << std::endl;
		}
		else
		{
			std::cout << "flag:" << flag << std::endl;
			std::cout << "znode create error... path:" << path << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

// 根据指定的path，获取znode节点的值
std::string ZkClient::GetData(const char *path)
{
    char buffer[64];
	int bufferlen = sizeof(buffer);
	int flag = zoo_get(m_zhandle, path, 0, buffer, &bufferlen, nullptr);
	if (flag != ZOK)
	{
		std::cout << "get znode error... path:" << path << std::endl;
		return "";
	}
	else
	{
		return buffer;
	}
}