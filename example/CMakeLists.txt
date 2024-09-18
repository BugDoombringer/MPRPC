# 定义源文件
set(PROVIDER_SOURCES
    userService.cc
    user.pb.cc
)

set(CONSUMER_SOURCES
    callUserService.cc
    user.pb.cc
)

# 添加可执行文件
add_executable(provider ${PROVIDER_SOURCES})
add_executable(consumer ${CONSUMER_SOURCES})

# 链接库
target_link_libraries(provider mprpc protobuf)
target_link_libraries(consumer mprpc protobuf)