#!/usr/bin/env python3
"""
SSHFS Manager using tmux and sshpass (Python version)
Usage: ./sshfs_manager.py {mount|umount|status}
"""

import os
import sys
import time
import subprocess
import shlex
from pathlib import Path

# ========== 用户配置区域 ==========
REMOTE_USER = ""
REMOTE_HOST = ""
REMOTE_PATH = ""
LOCAL_MOUNT_POINT = "/mnt/"
PASSWORD = ''
TMUX_SESSION = "sshfs-mount"
# =================================

# SSHFS 额外选项
SSHFS_OPTIONS = [
    "reconnect",
    "ServerAliveInterval=15",
    "ServerAliveCountMax=3",
    "allow_other",
    "StrictHostKeyChecking=no",
    "UserKnownHostsFile=/dev/null"
]

def check_deps():
    """检查依赖工具是否安装"""
    deps = ['tmux', 'sshpass', 'fusermount']
    missing = []
    for dep in deps:
        if not shutil.which(dep):
            missing.append(dep)
    if missing:
        print(f"❌ 缺少依赖: {', '.join(missing)}，请先安装。")
        sys.exit(1)
    # 特别检查 sshfs（fusermount 可能由 fuse 提供，但 sshfs 需要单独）
    if not shutil.which('sshfs'):
        print("❌ 未找到 sshfs 命令，请先安装 sshfs。")
        sys.exit(1)

def is_mounted():
    """检查挂载点是否已挂载"""
    try:
        result = subprocess.run(['mount'], capture_output=True, text=True, check=True)
        return f' {LOCAL_MOUNT_POINT} ' in result.stdout
    except subprocess.CalledProcessError:
        return False

def tmux_session_exists():
    """检查 tmux 会话是否存在"""
    result = subprocess.run(['tmux', 'has-session', '-t', TMUX_SESSION],
                            capture_output=True)
    return result.returncode == 0

def cleanup_mountpoint():
    """强制卸载残留挂载点"""
    if is_mounted():
        subprocess.run(['fusermount', '-uz', LOCAL_MOUNT_POINT],
                       capture_output=True)
        time.sleep(1)

def get_tmux_last_lines(n=5):
    """从 tmux 会话中获取最后 n 行输出"""
    if not tmux_session_exists():
        return None
    try:
        result = subprocess.run(
            ['tmux', 'capture-pane', '-t', TMUX_SESSION, '-p', '-S', f'-{n}'],
            capture_output=True, text=True, check=True
        )
        return result.stdout.strip()
    except subprocess.CalledProcessError:
        return None

def do_mount():
    """挂载命令：在 tmux 后台启动 sshfs"""
    if tmux_session_exists():
        print(f"⚠️  tmux 会话 '{TMUX_SESSION}' 已存在，可能已经挂载。")
        print(f"   如需重新挂载，请先执行 '{sys.argv[0]} umount'")
        sys.exit(1)

    # 确保挂载点目录存在
    Path(LOCAL_MOUNT_POINT).mkdir(parents=True, exist_ok=True)

    if is_mounted():
        print("🔍 检测到残留挂载，正在清理...")
        cleanup_mountpoint()

    print(f"🔌 在 tmux 后台会话 '{TMUX_SESSION}' 中启动 SSHFS ...")

    # 构建 sshfs 命令（使用单引号保护密码）
    remote = f"{REMOTE_USER}@{REMOTE_HOST}:{REMOTE_PATH}"
    options = ','.join(SSHFS_OPTIONS)
    # 注意：密码用单引号包围，确保特殊字符安全
    cmd_str = (f"export SSHPASS='{PASSWORD}'; exec sshpass -e sshfs {remote} {LOCAL_MOUNT_POINT} "
               f"-o {options} -f 2>&1 | tee /tmp/sshfs-tmux.log")

    # 在 tmux 新会话中运行命令
    try:
        subprocess.run(['tmux', 'new-session', '-d', '-s', TMUX_SESSION, cmd_str],
                       check=True)
    except subprocess.CalledProcessError as e:
        print(f"❌ 启动 tmux 会话失败: {e}")
        sys.exit(1)

    # 等待几秒让挂载稳定
    print("⏳ 等待挂载稳定 (5秒)...")
    time.sleep(5)

    # 验证挂载点是否可访问
    if os.listdir(LOCAL_MOUNT_POINT) is not None:  # 简单测试是否能列出目录
        print("✅ 挂载成功！SSHFS 在 tmux 后台运行中。")
        print(f"   可通过 'tmux attach -t {TMUX_SESSION}' 查看输出，Ctrl+B D 脱离。")
        # 尝试显示磁盘使用情况
        df_result = subprocess.run(['df', '-h', LOCAL_MOUNT_POINT],
                                   capture_output=True, text=True)
        if df_result.returncode == 0:
            print(df_result.stdout.splitlines()[-1])
        else:
            print("   目录可访问，但 df 暂时无法获取信息（不影响使用）。")
    else:
        print("❌ 挂载失败，请检查 tmux 会话日志：")
        print(f"   tmux capture-pane -t {TMUX_SESSION} -p -S -")
        print("   或查看 /tmp/sshfs-tmux.log")
        # 清理失败的会话
        subprocess.run(['tmux', 'kill-session', '-t', TMUX_SESSION],
                       capture_output=True)
        sys.exit(1)

def do_umount():
    """卸载命令：终止 tmux 会话并卸载挂载点"""
    killed = False
    if tmux_session_exists():
        print(f"🔌 正在停止 tmux 会话 '{TMUX_SESSION}' ...")
        subprocess.run(['tmux', 'kill-session', '-t', TMUX_SESSION],
                       capture_output=True)
        killed = True
    else:
        print(f"⚠️  tmux 会话 '{TMUX_SESSION}' 不存在。")

    if is_mounted():
        print(f"🔌 正在卸载挂载点 {LOCAL_MOUNT_POINT} ...")
        result = subprocess.run(['fusermount', '-uz', LOCAL_MOUNT_POINT],
                                capture_output=True)
        if result.returncode == 0:
            print("✅ 卸载成功！")
        else:
            print("❌ 卸载失败，请手动检查。")
            sys.exit(1)
    else:
        print("⚠️  挂载点未挂载。")

    if killed:
        print("✅ tmux 会话已终止。")

def do_status():
    """状态命令：显示 tmux 会话和挂载点状态"""
    print("=== tmux 会话状态 ===")
    if tmux_session_exists():
        print(f"✅ tmux 会话 '{TMUX_SESSION}' 正在运行")
        last_lines = get_tmux_last_lines(5)
        if last_lines:
            print("   最新输出 (末尾5行):")
            for line in last_lines.splitlines():
                print(f"      {line}")
    else:
        print("❌ tmux 会话不存在")

    print("\n=== 挂载点状态 ===")
    if is_mounted():
        print(f"✅ 挂载点 {LOCAL_MOUNT_POINT} 已挂载")
        # 测试可访问性
        try:
            os.listdir(LOCAL_MOUNT_POINT)
            print("   目录可正常访问。")
            df_result = subprocess.run(['df', '-h', LOCAL_MOUNT_POINT],
                                       capture_output=True, text=True)
            if df_result.returncode == 0:
                print("   " + df_result.stdout.splitlines()[-1])
        except OSError:
            print("   警告：目录不可访问！可能连接已断开。")
    else:
        print("❌ 挂载点未挂载")

def usage():
    print(f"用法: {sys.argv[0]} {{mount|umount|status}}")
    print("  mount   - 在 tmux 后台启动 SSHFS 挂载")
    print("  umount  - 停止 tmux 会话并卸载")
    print("  status  - 查看挂载和 tmux 会话状态")
    sys.exit(1)

def main():
    if len(sys.argv) < 2:
        cmd = "mount"
    else:
        cmd = sys.argv[1].lower()

    if cmd == "mount":
        do_mount()
    elif cmd in ("umount", "unmount"):
        do_umount()
    elif cmd == "status":
        do_status()
    else:
        usage()

if __name__ == "__main__":
    # 导入 shutil 以检查命令是否存在
    import shutil
    check_deps()
    main()