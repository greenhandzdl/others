#!/bin/bash
while true; do
    read -r -p "请输入内容（直接回车退出）: " input
    if [[ -z "$input" ]]; then
        echo "退出程序"
        break
    fi
    echo "$input" | rev
done