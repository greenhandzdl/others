#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import subprocess
import datetime
import os
import platform
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
    font = None
    # 获取操作系统类型
    system = platform.system()
    
    # 根据不同操作系统提供字体路径列表
    font_paths = []
    
    if system == "Darwin":  # macOS
        font_paths = [
            "/System/Library/Fonts/Supplemental/Arial Unicode.ttf",
            "/Library/Fonts/Arial Unicode.ttf",
            "/System/Library/Fonts/PingFang.ttc",
            "/System/Library/Fonts/STHeiti Light.ttc"
        ]
    elif system == "Windows":
        font_paths = [
            "C:\\Windows\\Fonts\\msyh.ttc",  # 微软雅黑
            "C:\\Windows\\Fonts\\simsun.ttc",  # 宋体
            "C:\\Windows\\Fonts\\simhei.ttf",  # 黑体
            "C:\\Windows\\Fonts\\Arial Unicode.ttf"
        ]
    else:  # Linux 和 BSD
        font_paths = [
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/wqy/wqy-microhei.ttc",  # 文泉驿微米黑
            "/usr/share/fonts/truetype/arphic/uming.ttc",  # AR PL UMing
            "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",  # Noto Sans CJK
            "/usr/local/share/fonts/wqy-microhei.ttc"  # BSD 可能的路径
        ]
    
    # 尝试加载字体列表中的字体
    for font_path in font_paths:
        try:
            font = ImageFont.truetype(font_path, 12)
            break  # 找到可用字体后跳出循环
        except IOError:
            continue  # 尝试下一个字体
    
    # 如果所有字体都无法加载，使用默认字体
    if font is None:
        print(f"警告: 在{system}系统上未找到合适的字体，将使用默认字体。中文可能无法正确显示。")
        font = ImageFont.load_default()
    
    # 计算图像大小
    lines = text.split('\n')
    line_height = 15  # 行高
    
    # 改进的宽度计算方法，考虑中文字符宽度
    def estimate_text_width(text):
        width = 0
        for char in text:
            # 中文字符（包括全角标点）通常是英文字符的两倍宽
            if ord(char) > 127:
                width += 16  # 中文字符宽度
            else:
                width += 8   # 英文字符宽度
        return width
    
    max_line_width = max([estimate_text_width(line) for line in lines])
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