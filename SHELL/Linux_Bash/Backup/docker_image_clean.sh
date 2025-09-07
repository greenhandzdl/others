#!/bin/bash

# Docker悬空镜像清理脚本
# 用于安全删除所有没有标签的镜像（悬空镜像）

set -e  # 出现任何错误时立即退出脚本

echo "=== Docker悬空镜像清理脚本 ==="
echo "开始时间: $(date)"

# 显示当前磁盘使用情况
echo -e "\n当前Docker磁盘使用情况:"
docker system df

# 列出所有悬空镜像（没有标签的镜像）
echo -e "\n扫描悬空镜像（没有标签的镜像）..."
dangling_images=$(docker images -q -f "dangling=true")

if [ -z "$dangling_images" ]; then
    echo -e "\n没有找到任何悬空镜像。"
    echo -e "\n操作完成。"
    exit 0
fi

echo -e "\n找到以下悬空镜像（即将被删除）:"
docker images --filter "dangling=true"

# 计算可释放的空间
echo -e "\n计算可释放的空间..."
total_size=0
while IFS= read -r id; do
    if [ -n "$id" ]; then
        size=$(docker inspect --format='{{.Size}}' "$id" 2>/dev/null || echo 0)
        total_size=$((total_size + size))
    fi
done <<< "$dangling_images"

# 转换为人类可读的格式
human_readable_size=$(numfmt --to=iec-i --suffix=B $total_size 2>/dev/null || echo "$total_size B")

# 确认操作
echo -e "\n⚠️  以上镜像将被删除，预计可释放: $human_readable_size"
read -p "是否要继续删除操作？(y/N): " confirm

if [[ ! "$confirm" =~ ^[Yy]$ ]]; then
    echo "操作已取消。"
    exit 0
fi

# 执行删除操作
echo -e "\n开始删除悬空镜像..."
docker rmi $dangling_images 2>/dev/null || echo "一些镜像无法删除（可能正在被使用），将继续尝试..."

# 使用prune命令确保清理（更温和的方式）
echo -e "\n使用docker image prune进行最终清理..."
docker image prune -f

# 显示清理后的磁盘使用情况
echo -e "\n清理后的Docker磁盘使用情况:"
docker system df

echo -e "\n✅ 镜像清理完成!"
echo "结束时间: $(date)"