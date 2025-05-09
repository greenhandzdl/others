#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# python termToImg.py "find .  -type f -exec echo '文件: {}' \; -exec cat {} \; -exec echo '\n-----------------------------------\n' \;"
import subprocess
import datetime
import os
import platform
from PIL import Image, ImageDraw, ImageFont
import sys
import requests
import shutil
import zipfile
import io
import time

# 用户命令提示符常量
PS1_PROMPT = "❯ "

# 字体下载链接常量
FONT_URLS = {
    "source_han_sans": "https://github.com/adobe-fonts/source-han-sans/releases/download/2.004R/SourceHanSansSC.zip",
    "wqy_microhei": "https://sourceforge.net/projects/wqy/files/wqy-microhei/0.2.0-beta/wqy-microhei-0.2.0-beta.tar.gz/download"
}

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
        # 返回命令和输出结果
        return command, result.stdout
    except subprocess.CalledProcessError as e:
        # 如果命令执行失败，打印错误信息
        print(f"命令执行失败: {e}")
        print(f"错误输出: {e.stderr}")
        return command, f"命令执行失败: {e}\n错误输出: {e.stderr}"

def ensure_font_dir():
    """
    确保字体目录存在
    """
    # 获取脚本所在目录
    script_dir = os.path.dirname(os.path.abspath(__file__))
    font_dir = os.path.join(script_dir, "fonts")
    
    # 如果字体目录不存在，创建它
    if not os.path.exists(font_dir):
        os.makedirs(font_dir)
        print(f"已创建字体目录: {font_dir}")
    
    return font_dir

def download_font(font_name, font_url, font_dir):
    """
    下载字体到指定目录
    """
    font_path = os.path.join(font_dir, font_name)
    
    # 如果字体已存在，直接返回路径
    if os.path.exists(font_path):
        print(f"字体已存在: {font_path}")
        return font_path
    
    print(f"正在下载字体: {font_name}...")
    try:
        # 下载字体文件
        response = requests.get(font_url, stream=True)
        response.raise_for_status()  # 确保请求成功
        
        # 检查是否是zip文件
        if font_name.endswith('.zip'):
            # 解压zip文件
            with zipfile.ZipFile(io.BytesIO(response.content)) as zip_ref:
                # 获取zip中的ttf/otf文件
                font_files = [f for f in zip_ref.namelist() if f.endswith(('.ttf', '.otf', '.ttc'))]
                if not font_files:
                    print("压缩包中没有找到字体文件")
                    return None
                
                # 解压第一个字体文件
                extracted_font = font_files[0]
                zip_ref.extract(extracted_font, font_dir)
                extracted_path = os.path.join(font_dir, extracted_font)
                
                # 重命名为简单的名称
                simple_name = os.path.basename(extracted_font)
                new_path = os.path.join(font_dir, simple_name)
                if extracted_path != new_path:
                    shutil.move(extracted_path, new_path)
                
                print(f"已解压并保存字体: {new_path}")
                return new_path
        else:
            # 直接保存文件
            with open(font_path, 'wb') as f:
                for chunk in response.iter_content(chunk_size=8192):
                    f.write(chunk)
            print(f"已下载并保存字体: {font_path}")
            return font_path
    except Exception as e:
        print(f"下载字体失败: {e}")
        return None

def download_chinese_fonts(font_dir):
    """
    下载中文字体
    """
    fonts = [
        # 思源黑体
        ("SourceHanSansSC-Regular.otf", FONT_URLS["source_han_sans"]),
        # 文泉驿微米黑
        ("wqy-microhei.ttc", FONT_URLS["wqy_microhei"])
    ]
    
    downloaded_fonts = []
    for font_name, font_url in fonts:
        font_path = os.path.join(font_dir, font_name)
        if os.path.exists(font_path):
            downloaded_fonts.append(font_path)
            continue
            
        # 尝试下载字体
        downloaded_font = download_font(font_name, font_url, font_dir)
        if downloaded_font:
            downloaded_fonts.append(downloaded_font)
            # 成功下载一个字体后就返回
            return downloaded_fonts
    
    return downloaded_fonts

def text_to_image(text, output_path):
    """
    将文本转换为图像并保存
    """
    # 设置字体和大小
    font = None
    # 获取操作系统类型
    system = platform.system()
    
    # 确保字体目录存在
    font_dir = ensure_font_dir()
    
    # 首先检查本地缓存的字体
    local_font_paths = [os.path.join(font_dir, f) for f in os.listdir(font_dir) if f.endswith(('.ttf', '.otf', '.ttc'))] if os.path.exists(font_dir) else []
    
    # 根据不同操作系统提供字体路径列表
    system_font_paths = []
    
    if system == "Darwin":  # macOS
        system_font_paths = [
            "/System/Library/Fonts/Supplemental/Arial Unicode.ttf",
            "/Library/Fonts/Arial Unicode.ttf",
            "/System/Library/Fonts/PingFang.ttc",
            "/System/Library/Fonts/STHeiti Light.ttc"
        ]
    elif system == "Windows":
        system_font_paths = [
            "C:\\Windows\\Fonts\\msyh.ttc",  # 微软雅黑
            "C:\\Windows\\Fonts\\simsun.ttc",  # 宋体
            "C:\\Windows\\Fonts\\simhei.ttf",  # 黑体
            "C:\\Windows\\Fonts\\Arial Unicode.ttf"
        ]
    else:  # Linux 和 BSD
        system_font_paths = [
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/wqy/wqy-microhei.ttc",  # 文泉驿微米黑
            "/usr/share/fonts/truetype/arphic/uming.ttc",  # AR PL UMing
            "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",  # Noto Sans CJK
            "/usr/local/share/fonts/wqy-microhei.ttc"  # BSD 可能的路径
        ]
    
    # 合并本地字体和系统字体路径，优先使用本地字体
    font_paths = local_font_paths + system_font_paths
    
    # 尝试加载字体列表中的字体
    for font_path in font_paths:
        try:
            font = ImageFont.truetype(font_path, 12)
            print(f"使用字体: {font_path}")
            break  # 找到可用字体后跳出循环
        except IOError:
            continue  # 尝试下一个字体
    
    # 如果所有字体都无法加载，尝试下载中文字体
    if font is None:
        print(f"在{system}系统上未找到合适的字体，尝试下载中文字体...")
        downloaded_fonts = download_chinese_fonts(font_dir)
        
        # 尝试使用下载的字体
        for font_path in downloaded_fonts:
            try:
                font = ImageFont.truetype(font_path, 12)
                print(f"使用下载的字体: {font_path}")
                break
            except IOError:
                continue
    
    # 如果仍然无法加载字体，使用默认字体
    if font is None:
        print(f"警告: 无法加载或下载中文字体，将使用默认字体。中文可能无法正确显示。")
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
    cmd, output = execute_command(command)
    
    # 获取当前日期作为文件名
    today = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    
    # 获取用户当前工作目录（而非脚本所在目录）
    work_dir = os.getcwd()
    
    # 设置输出文件路径（在用户工作目录下）
    output_path = os.path.join(work_dir, f"{today}.png")
    
    # 创建包含命令和输出的完整文本
    # 使用预定义的PS1提示符常量
    full_text = f"{PS1_PROMPT}{cmd}\n\n{output}"
    
    # 将输出转换为图像并保存
    text_to_image(full_text, output_path)

if __name__ == "__main__":
    main()