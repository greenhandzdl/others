#!/usr/bin/env python3
import sys
import os
import requests
import urllib.parse

# VITS服务器URL常量
SERVER_URL = "http://192.168.31.2:23456"

def validate_arguments():
    """验证命令行参数并返回id和输入文件路径"""
    # 检查命令行参数
    if len(sys.argv) != 3:
        print("Usage: python vits-get.py <id> <input_file.md>")
        sys.exit(1)
    
    # 获取命令行参数
    try:
        id_param = int(sys.argv[1])
    except ValueError:
        print("Error: id must be an integer")
        sys.exit(1)
    
    input_file = sys.argv[2]
    
    # 检查输入文件是否存在
    if not os.path.exists(input_file):
        print(f"Error: Input file '{input_file}' does not exist")
        sys.exit(1)
    
    return id_param, input_file

def ensure_output_directory():
    """确保输出目录存在"""
    # 获取脚本所在目录
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # 在脚本所在目录下创建outputs文件夹
    output_dir = os.path.join(script_dir, "outputs")
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    return output_dir

def read_input_file(input_file):
    """读取输入文件并返回内容行"""
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        return lines
    except Exception as e:
        print(f"Error reading input file: {e}")
        sys.exit(1)

def build_request_url(id_param, text):
    """构建请求URL"""
    encoded_text = urllib.parse.quote(text)
    return f"{SERVER_URL}/voice/vits?id={id_param}&text={encoded_text}"

def download_voice(url, output_file, text):
    """下载语音文件并保存"""
    try:
        # 发送HTTP请求并获取WAV文件，设置超时时间为10秒
        print(f"Connecting to: {url}")
        print(f"Server address: {SERVER_URL}")
        response = requests.get(url, timeout=10)
        
        # 检查响应状态
        if response.status_code == 200:
            # 保存WAV文件
            with open(output_file, 'wb') as f:
                f.write(response.content)
            print(f"Saved to: {output_file}")
            return True
        else:
            print(f"Error: HTTP request failed with status code {response.status_code}")
            print(f"Response content: {response.text[:200]}")
            return False
    except requests.exceptions.ConnectTimeout:
        print(f"Error: Connection timeout when downloading voice for '{text}'")
        print(f"Please check if the server {SERVER_URL} is running and accessible")
        return False
    except requests.exceptions.ConnectionError as e:
        print(f"Error downloading voice for '{text}': {e}")
        print(f"Connection error details: {str(e)}")
        print(f"Please check network connectivity to {SERVER_URL}")
        return False
    except Exception as e:
        print(f"Error downloading voice for '{text}': {e}")
        print(f"Exception type: {type(e).__name__}")
        return False

def process_text_lines(lines, id_param, output_dir):
    """处理文本行并下载对应的语音"""
    success_count = 0
    total_valid_lines = 0
    
    for line in lines:
        text = line.strip()
        if not text:  # 跳过空行
            continue
        
        total_valid_lines += 1
        
        # 构建URL
        url = build_request_url(id_param, text)
        
        # 构建输出文件路径
        output_file = os.path.join(output_dir, f"{text}.wav")
        
        print(f"Downloading voice for text: '{text}'")
        
        if download_voice(url, output_file, text):
            success_count += 1
    
    return success_count, total_valid_lines

def main():
    # 验证参数
    id_param, input_file = validate_arguments()
    
    # 确保输出目录存在
    output_dir = ensure_output_directory()
    
    # 读取输入文件
    lines = read_input_file(input_file)
    
    # 处理文本行并下载语音
    success_count, total_valid_lines = process_text_lines(lines, id_param, output_dir)
    
    # 输出结果统计
    print(f"All voice files have been downloaded. Success: {success_count}/{total_valid_lines}")

if __name__ == "__main__":
    main()