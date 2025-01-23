#!/bin/bash

# 设置特殊字符
SPECIAL_CHAR="pqclean_sntrup857_clean/"

# 找出当前目录及其子目录中的所有.c文件
find . -name "*.c" -type f | while read -r file; do
    # 提取文件名（不包括路径）
    filename=$(basename -- "$file")
    # 输出带有特殊字符的文件名
    echo "${SPECIAL_CHAR}${filename}"
done