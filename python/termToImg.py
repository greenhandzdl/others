#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import subprocess
import datetime
import os
from PIL import Image, ImageDraw, ImageFont
import sys

def execute_command(command):
    """
    执行命令并返回输出结果
    """
    try:
        # 使用subprocess执行命令，捕获输出
        result = subprocess.run(command, shell=True, check=True, 
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                               universal_newlines=True)
        # 输出到终端
        print(result.stdout)
        if result.stderr:
            print("错误信息:", result.stderr)
        return result.stdout
    except subprocess.CalledProcessError as e:
        # 如果命令执行失败，打印错误信息
        print(f"命令执行失败: {e}")
        print(f"错误输出: {e.stderr}")
        return f"命令执行失败: {e}\n错误输出: {e.stderr}"

def text_to_image(text, output_path):
    """
    将文本转换为图像并保存
    """
    # 设置字体和大小
    try:
        # 尝试使用系统字体，根据操作系统可能需要调整路径
        font = ImageFont.truetype("/System/Library/Fonts/Monaco.ttf", 12)  # macOS字体路径
    except IOError:
        # 如果找不到指定字体，使用默认字体
        font = ImageFont.load_default()
    
    # 计算图像大小
    lines = text.split('\n')
    line_height = 15  # 行高
    max_line_width = max([len(line) for line in lines]) * 8  # 估计每个字符的宽度
    img_width = max(max_line_width, 800)  # 最小宽度800像素
    img_height = len(lines) * line_height + 20  # 额外添加一些边距
    
    # 创建图像
    image = Image.new('RGB', (img_width, img_height), color=(255, 255, 255))
    draw = ImageDraw.Draw(image)
    
    # 绘制文本
    y_position = 10
    for line in lines:
        draw.text((10, y_position), line, font=font, fill=(0, 0, 0))
        y_position += line_height
    
    # 保存图像
    image.save(output_path)
    print(f"图像已保存到: {output_path}")

def main():
    # 检查是否提供了命令
    if len(sys.argv) < 2:
        print("用法: python termToImg.py <命令>")
        sys.exit(1)
    
    # 获取命令（将所有参数组合成一个命令）
    command = ' '.join(sys.argv[1:])
    
    # 执行命令
    output = execute_command(command)
    
    # 获取当前日期作为文件名
    today = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    
    # 获取用户当前工作目录（而非脚本所在目录）
    work_dir = os.getcwd()
    
    # 设置输出文件路径（在用户工作目录下）
    output_path = os.path.join(work_dir, f"{today}.png")
    
    # 将输出转换为图像并保存
    text_to_image(output, output_path)

if __name__ == "__main__":
    main()