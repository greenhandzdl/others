#!/usr/bin/env python3
"""
Unity 项目备份脚本
用法: python backup_unity_project.py <unity_project_path>
输出: ./outputs/{project_name}_backup_{YYYYMMDD}.tar.zstd
"""

import argparse
import os
import sys
from datetime import datetime


# Unity 项目中需要备份的目录和文件
INCLUDE_PATTERNS = [
    "Assets",
    "Packages",
    "ProjectSettings",
]

# Unity 项目中需要排除的目录（可以重新生成）
EXCLUDE_DIRS = [
    "Library",
    "Temp",
    "obj",
    "Logs",
    ".vs",
    ".idea",
    "Builds",
    "Build",
    ".gradle",
    "UserSettings/EditorUserSettings.asset.lock",
]

# 需要包含的根目录文件
INCLUDE_ROOT_FILES = [
    ".gitignore",
    "Packages-lock.json",
]


def get_project_name(project_path: str) -> str:
    """获取项目名称（不带路径）"""
    return os.path.basename(os.path.normpath(project_path))


def create_output_path(project_name: str, output_dir: str = "outputs") -> str:
    """生成输出文件路径"""
    date_str = datetime.now().strftime("%Y%m%d")
    os.makedirs(output_dir, exist_ok=True)
    return os.path.join(output_dir, f"{project_name}_backup_{date_str}.tar.zstd")


def build_tar_command(project_path: str, output_path: str) -> list:
    """构建 tar 命令"""
    cmd = ["tar", "--zstd", "-cvf", output_path]

    # 添加排除项
    for exclude in EXCLUDE_DIRS:
        cmd.extend(["--exclude", exclude])

    # 切换到项目目录
    cmd.extend(["-C", project_path])

    # 添加需要备份的内容
    for pattern in INCLUDE_PATTERNS:
        cmd.append(pattern)

    for filename in INCLUDE_ROOT_FILES:
        filepath = os.path.join(project_path, filename)
        if os.path.exists(filepath):
            cmd.append(filename)

    return cmd


def main():
    parser = argparse.ArgumentParser(
        description="备份 Unity 项目为 tar.zstd 压缩包"
    )
    parser.add_argument(
        "project_path",
        help="Unity 项目路径"
    )
    parser.add_argument(
        "-o", "--output",
        help="输出文件路径（默认: ./outputs/{project}_backup_{date}.tar.zstd）"
    )

    args = parser.parse_args()

    project_path = os.path.abspath(args.project_path)

    # 验证项目路径
    if not os.path.exists(project_path):
        print(f"错误: 路径不存在: {project_path}", file=sys.stderr)
        sys.exit(1)

    # 检查是否有 Assets 目录
    assets_path = os.path.join(project_path, "Assets")
    if not os.path.exists(assets_path):
        print(f"警告: 路径可能不是 Unity 项目（缺少 Assets 目录）", file=sys.stderr)

    # 获取项目名称和输出路径
    project_name = get_project_name(project_path)
    output_path = args.output or create_output_path(project_name)

    print(f"项目: {project_name}")
    print(f"输出: {output_path}")

    # 构建并执行命令
    cmd = build_tar_command(project_path, output_path)

    print(f"\n执行: {' '.join(cmd)}\n")

    import subprocess
    result = subprocess.run(cmd)

    if result.returncode == 0:
        # 显示输出文件大小
        size = os.path.getsize(output_path)
        size_mb = size / (1024 * 1024)
        print(f"\n备份完成: {output_path}")
        print(f"文件大小: {size_mb:.2f} MB")
    else:
        print(f"\n备份失败，返回码: {result.returncode}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()