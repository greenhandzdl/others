#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Redis备份文件清理工具

这个脚本用于自动清理Redis的旧备份文件，包括RDB文件和AOF文件。
可以根据文件的修改时间或创建日期来删除超过特定时间的备份文件，
同时保留最新的几个备份以确保数据安全。

使用方法:
    python redis_cleanup.py [选项] <Redis数据目录路径>

选项:
    --keep-days DAYS       保留最近DAYS天内的备份文件 (默认: 7)
    --keep-files NUM       每种类型至少保留NUM个最新的备份文件 (默认: 3)
    --dry-run              仅显示要删除的文件，不实际删除
    --verbose              显示详细信息
    --help                 显示帮助信息

示例:
    python redis_cleanup.py --keep-days 14 --keep-files 5 /path/to/redis/data
"""

import os
import sys
import time
import argparse
from datetime import datetime, timedelta
import shutil


def get_file_info(file_path):
    """获取文件信息，包括修改时间和大小"""
    try:
        stat = os.stat(file_path)
        return {
            'path': file_path,
            'mtime': stat.st_mtime,  # 修改时间
            'size': stat.st_size,    # 文件大小（字节）
            'mtime_str': datetime.fromtimestamp(stat.st_mtime).strftime('%Y-%m-%d %H:%M:%S')
        }
    except Exception as e:
        print(f"警告: 无法获取文件 {file_path} 的信息: {e}", file=sys.stderr)
        return None


def get_backup_files(data_dir):
    """获取所有备份文件信息并按类型分类"""
    if not os.path.isdir(data_dir):
        print(f"错误: {data_dir} 不是一个有效的目录", file=sys.stderr)
        sys.exit(1)
        
    # 检查appendonlydir目录是否存在
    aof_dir = os.path.join(data_dir, 'appendonlydir')
    aof_exists = os.path.isdir(aof_dir)
    
    backup_files = {
        'rdb': [],  # RDB文件
        'aof_base': [],  # AOF基础文件
        'aof_incr': [],  # AOF增量文件
        'aof_manifest': []  # AOF清单文件
    }
    
    # 查找RDB文件
    for filename in os.listdir(data_dir):
        if filename.endswith('.rdb'):
            file_path = os.path.join(data_dir, filename)
            file_info = get_file_info(file_path)
            if file_info:
                backup_files['rdb'].append(file_info)
    
    # 如果存在AOF目录，查找AOF相关文件
    if aof_exists:
        for filename in os.listdir(aof_dir):
            file_path = os.path.join(aof_dir, filename)
            file_info = get_file_info(file_path)
            if not file_info:
                continue
                
            if filename.endswith('.base.rdb'):
                backup_files['aof_base'].append(file_info)
            elif filename.endswith('.incr.aof'):
                backup_files['aof_incr'].append(file_info)
            elif filename.endswith('.manifest'):
                backup_files['aof_manifest'].append(file_info)
    
    # 按修改时间排序（最新的在前）
    for file_type in backup_files:
        backup_files[file_type].sort(key=lambda x: x['mtime'], reverse=True)
        
    return backup_files


def cleanup_backup_files(data_dir, keep_days=7, keep_files=3, dry_run=False, verbose=False):
    """清理旧的备份文件"""
    backup_files = get_backup_files(data_dir)
    cutoff_time = time.time() - (keep_days * 24 * 60 * 60)  # 计算截止时间
    
    files_to_delete = []
    saved_space = 0
    
    for file_type, files in backup_files.items():
        if verbose:
            print(f"\n发现 {len(files)} 个 {file_type} 文件")
            
        # 保留最新的keep_files个文件
        keep_newest = files[:keep_files]
        candidates_for_deletion = files[keep_files:]
        
        # 从候选删除列表中，删除那些在保留天数内的文件
        for file_info in candidates_for_deletion:
            if file_info['mtime'] < cutoff_time:
                files_to_delete.append(file_info)
                saved_space += file_info['size']
                if verbose:
                    print(f"将删除: {file_info['path']} (修改于 {file_info['mtime_str']})")
            else:
                if verbose:
                    print(f"保留: {file_info['path']} (修改于 {file_info['mtime_str']}, 在保留期内)")
        
        # 显示保留的最新文件
        if verbose and keep_newest:
            for file_info in keep_newest:
                print(f"保留: {file_info['path']} (修改于 {file_info['mtime_str']}, 最新文件)")
    
    # 执行删除操作
    if files_to_delete:
        if dry_run:
            print(f"\n[模拟运行] 将删除 {len(files_to_delete)} 个文件，释放 {format_size(saved_space)} 空间")
        else:
            for file_info in files_to_delete:
                try:
                    os.remove(file_info['path'])
                    print(f"已删除: {file_info['path']}")
                except Exception as e:
                    print(f"删除文件 {file_info['path']} 失败: {e}", file=sys.stderr)
            print(f"\n已删除 {len(files_to_delete)} 个文件，释放了 {format_size(saved_space)} 空间")
    else:
        print("没有需要删除的备份文件")


def format_size(size_bytes):
    """格式化文件大小显示"""
    if size_bytes < 1024:
        return f"{size_bytes} 字节"
    elif size_bytes < 1024 * 1024:
        return f"{size_bytes/1024:.2f} KB"
    elif size_bytes < 1024 * 1024 * 1024:
        return f"{size_bytes/(1024*1024):.2f} MB"
    else:
        return f"{size_bytes/(1024*1024*1024):.2f} GB"


def main():
    parser = argparse.ArgumentParser(description='Redis备份文件清理工具')
    parser.add_argument('data_dir', help='Redis数据目录路径')
    parser.add_argument('--keep-days', type=int, default=7, help='保留最近几天的备份文件 (默认: 7)')
    parser.add_argument('--keep-files', type=int, default=3, help='每种类型至少保留几个最新的备份文件 (默认: 3)')
    parser.add_argument('--dry-run', action='store_true', help='仅显示要删除的文件，不实际删除')
    parser.add_argument('--verbose', action='store_true', help='显示详细信息')
    
    args = parser.parse_args()
    
    # 检查目录是否存在
    if not os.path.exists(args.data_dir):
        print(f"错误: 目录 '{args.data_dir}' 不存在", file=sys.stderr)
        sys.exit(1)
    
    print(f"开始清理 Redis 备份文件...")
    print(f"数据目录: {args.data_dir}")
    print(f"保留天数: {args.keep_days} 天")
    print(f"每种类型保留文件数: {args.keep_files}")
    if args.dry_run:
        print("模式: 模拟运行 (不会实际删除文件)")
    
    cleanup_backup_files(
        args.data_dir,
        keep_days=args.keep_days,
        keep_files=args.keep_files,
        dry_run=args.dry_run,
        verbose=args.verbose
    )


if __name__ == '__main__':
    main()