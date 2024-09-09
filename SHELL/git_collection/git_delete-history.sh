#!/bin/bash
# 描述：此脚本将删除本地所有提交历史。请谨慎使用！

# 获取当前分支名称
branch=$(git branch --show-current)

# 重置当前分支到初始提交
git reset --hard HEAD

# 强制推送重置后的分支到远程仓库
git push origin $branch -f

# 删除所有本地引用
git reflog expire --expire=now --all
git gc --prune=now

# 输出完成消息
echo "本地提交历史已删除。"