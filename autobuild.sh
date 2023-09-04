#!/bin/bash

set -e

# 编译
rm -rf `pwd`/build/*
cd `pwd`/build && cmake .. && make
cd ..

# 刷新链接库缓存
ldconfig
