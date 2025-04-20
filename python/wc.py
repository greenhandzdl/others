#!/usr/bin/env python3
# 这个程序递归访问指定目录下所有文件,统计字符数、行数和单词数
import os
import sys
import argparse
import fnmatch
from collections import defaultdict

def count_file_stats(file_path):
    """统计单个文件的字符数、行数和单词数"""
    try:
        with open(file_path, 'r', encoding='utf-8', errors='replace') as f:
            content = f.read()
            lines = content.splitlines()
            words = content.split()
            chars = len(content)
            return {
                'chars': chars,
                'lines': len(lines),
                'words': len(words)
            }
    except (PermissionError, IsADirectoryError):
        return {'chars': 0, 'lines': 0, 'words': 0}
    except Exception as e:
        print(f"警告: 无法读取文件 {file_path}: {e}", file=sys.stderr)
        return {'chars': 0, 'lines': 0, 'words': 0}

def get_stats(path, exclude=None, include=None):
    """递归统计目录下所有文件的字符数、行数和单词数"""
    stats = defaultdict(int)
    
    if os.path.isfile(path):
        # 检查文件是否应该被包含
        filename = os.path.basename(path)
        if include and not any(fnmatch.fnmatch(filename, pattern) for pattern in include):
            return stats
        if exclude and any(fnmatch.fnmatch(filename, pattern) for pattern in exclude):
            return stats
            
        file_stats = count_file_stats(path)
        for key, value in file_stats.items():
            stats[key] += value
    elif os.path.isdir(path):
        try:
            for item in os.listdir(path):
                item_path = os.path.join(path, item)
                item_stats = get_stats(item_path, exclude, include)
                for key, value in item_stats.items():
                    stats[key] += value
        except PermissionError:
            print(f"警告: 无权限访问目录 {path}", file=sys.stderr)
        except Exception as e:
            print(f"警告: 访问目录 {path} 时出错: {e}", file=sys.stderr)
    
    return stats

def format_number(num):
    """格式化数字，添加千位分隔符"""
    return f"{num:,}"

def main():
    # 解析命令行参数
    parser = argparse.ArgumentParser(description='统计目录下所有文件的字符数、行数和单词数')
    parser.add_argument('path', nargs='?', default=os.getcwd(),
                        help='要统计的目录或文件路径 (默认为当前目录)')
    parser.add_argument('-e', '--exclude', action='append',
                        help='排除的文件模式 (可多次使用，如 *.log)')
    parser.add_argument('-i', '--include', action='append',
                        help='仅包含的文件模式 (可多次使用，如 *.py)')
    parser.add_argument('-c', '--chars-only', action='store_true',
                        help='仅显示字符数')
    parser.add_argument('-l', '--lines-only', action='store_true',
                        help='仅显示行数')
    parser.add_argument('-w', '--words-only', action='store_true',
                        help='仅显示单词数')
    
    args = parser.parse_args()
    
    # 检查路径是否存在
    if not os.path.exists(args.path):
        print(f"错误: 路径 '{args.path}' 不存在", file=sys.stderr)
        sys.exit(1)
    
    # 获取统计结果
    stats = get_stats(args.path, args.exclude, args.include)
    
    # 根据参数决定输出内容
    if args.chars_only:
        print(format_number(stats['chars']))
    elif args.lines_only:
        print(format_number(stats['lines']))
    elif args.words_only:
        print(format_number(stats['words']))
    else:
        print(f"字符数: {format_number(stats['chars'])}")
        print(f"行数: {format_number(stats['lines'])}")
        print(f"单词数: {format_number(stats['words'])}")

if __name__ == '__main__':
    main()
    