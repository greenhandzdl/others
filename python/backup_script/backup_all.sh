#!/bin/bash

# 遍历当前目录下的所有文件夹并执行备份

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BACKUP_SCRIPT="$SCRIPT_DIR/backup_unity_project.py"

# 需要排除的目录
EXCLUDE_DIRS=(
    "outputs"
    "backup_unity_project.py"
    "backup_all.sh"
)

# 检查备份脚本是否存在
if [[ ! -f "$BACKUP_SCRIPT" ]]; then
    echo "错误: 找不到 backup_unity_project.py"
    exit 1
fi

# 遍历当前目录下的所有项
for item in */; do
    # 去掉尾部的 /
    item="${item%/}"

    # 检查是否在排除列表中
    skip=false
    for exclude in "${EXCLUDE_DIRS[@]}"; do
        if [[ "$item" == "$exclude" ]]; then
            skip=true
            break
        fi
    done

    if [[ "$skip" == true ]]; then
        echo "跳过: $item (排除列表)"
        continue
    fi

    # 检查是否为目录
    if [[ -d "$item" ]]; then
        # 检查是否为Unity项目（有Assets目录）
        if [[ -d "$item/Assets" ]]; then
            echo "========================================"
            echo "开始备份: $item"
            echo "========================================"
             python3 "$BACKUP_SCRIPT" "$item"
            echo ""
        else
            echo "跳过: $item (不是Unity项目，缺少Assets目录)"
        fi
    fi
done

echo "全部完成!"
