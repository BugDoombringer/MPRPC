#!/bin/bash

#set -e

#rm -rf `pwd`/build/*
#cd `pwd`/build &&
#	cmake .. &&
#	make
#cd ..
#cp -r `pwd`/src/include `pwd`/lib





#!/bin/bash

set -e

# 获取当前工作目录
CURRENT_DIR=$(pwd)
BUILD_DIR="$CURRENT_DIR/build"
INCLUDE_DIR="$CURRENT_DIR/src/include"
LIB_DIR="$CURRENT_DIR/lib"

# 清理build目录
rm -rf "$BUILD_DIR"

# 创建build目录
mkdir -p "$BUILD_DIR"

# 进入build目录，执行构建
cd "$BUILD_DIR"
cmake ..
make

# 复制头文件到 lib 目录
mkdir -p "$LIB_DIR"
cp -r "$INCLUDE_DIR" "$LIB_DIR"

# 返回到初始目录
cd "$CURRENT_DIR"
