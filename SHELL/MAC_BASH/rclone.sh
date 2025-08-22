#!/bin/zsh

# 脚本名称: 123pan
# 功能: 挂载123pan网盘到本地目录

# 配置变量
MOUNT_NAME="123pan"
MOUNT_POINT="$HOME/mnt/123pan"
LOG_DIR="$HOME/.rclone/logs"
LOG_FILE="$LOG_DIR/123pan.log"
RCLONE_REMOTE="123pan:"

# 创建日志目录
mkdir -p "$LOG_DIR"

# 函数: 输出带颜色的消息
color_echo() {
    local color=$1
    shift
    case $color in
        red) echo -e "\033[31m$*\033[0m" ;;
        green) echo -e "\033[32m$*\033[0m" ;;
        yellow) echo -e "\033[33m$*\033[0m" ;;
        *) echo "$*" ;;
    esac
}

# 函数: 检查并终止现有挂载进程
terminate_existing_mount() {
    color_echo yellow "检查现有挂载进程..."
    
    # 查找与当前挂载相关的进程
    local pids=$(pgrep -f "rclone mount.*$MOUNT_NAME" || true)
    
    if [ -n "$pids" ]; then
        color_echo yellow "找到现有挂载进程: $pids"
        
        # 尝试正常卸载
        if mount | grep -q "$MOUNT_POINT"; then
            color_echo yellow "尝试卸载 $MOUNT_POINT..."
            umount "$MOUNT_POINT" 2>/dev/null && \
                color_echo green "成功卸载 $MOUNT_POINT" || \
                color_echo yellow "卸载失败，尝试强制终止进程"
        fi
        
        # 终止相关进程
        pkill -f "rclone mount.*$MOUNT_NAME" 2>/dev/null && \
            color_echo green "已终止现有挂载进程" || \
            color_echo yellow "没有找到需要终止的进程"
        
        # 等待进程完全终止
        sleep 2
    else
        color_echo green "未找到现有挂载进程"
    fi
}

# 函数: 清理并重新创建挂载点
prepare_mount_point() {
    color_echo yellow "准备挂载点目录..."
    
    # 检查目录是否已被挂载
    if mount | grep -q "$MOUNT_POINT"; then
        color_echo red "错误: $MOUNT_POINT 仍被挂载，请手动卸载"
        return 1
    fi
    
    # 删除现有目录（如果存在）
    if [ -d "$MOUNT_POINT" ]; then
        rm -rf "$MOUNT_POINT" && \
            color_echo green "已删除旧目录" || \
            color_echo red "删除目录失败"
    fi
    
    # 创建新目录
    mkdir -p "$MOUNT_POINT" && \
        color_echo green "已创建新目录: $MOUNT_POINT" || \
        color_echo red "创建目录失败"
}

# 函数: 执行挂载操作
perform_mount() {
    color_echo yellow "开始挂载 $MOUNT_NAME..."
    
    # 执行挂载命令
    rclone mount \
        --vfs-cache-mode writes \
        --daemon \
        --log-file "$LOG_FILE" \
        --log-level INFO \
        --daemon-timeout 30s \
        "$RCLONE_REMOTE" "$MOUNT_POINT"
    
    # 检查是否成功
    sleep 2
    if pgrep -f "rclone mount.*$MOUNT_NAME" > /dev/null; then
        color_echo green "$MOUNT_NAME 已成功挂载到 $MOUNT_POINT"
        color_echo green "日志文件: $LOG_FILE"
        return 0
    else
        color_echo red "挂载失败，请查看日志: $LOG_FILE"
        tail -n 10 "$LOG_FILE" 2>/dev/null
        return 1
    fi
}

# 主执行流程
main() {
    color_echo green "===== 开始挂载 $MOUNT_NAME ====="
    
    # 检查rclone配置
    if ! rclone listremotes | grep -q "^$MOUNT_NAME:"; then
        color_echo red "错误: 未找到rclone远程配置 '$MOUNT_NAME'"
        color_echo yellow "请先运行: rclone config"
        return 1
    fi
    
    # 执行挂载前准备
    terminate_existing_mount
    prepare_mount_point || return 1
    
    # 执行挂载
    perform_mount
}

# 执行主函数
main "$@"
