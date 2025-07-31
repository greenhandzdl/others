#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys

def main():
    print("字符串反转工具 (直接回车退出)")
    while True:
        try:
            # 获取用户输入
            user_input = input("请输入内容: ")
            
            # 检测空输入退出
            if user_input == '':
                print("程序已退出")
                break
                
            # 反转并输出字符串
            reversed_str = user_input[::-1]
            print(reversed_str)
            
        except KeyboardInterrupt:
            print("\n检测到中断请求，程序退出")
            sys.exit(0)
        except EOFError:
            print("\n程序已退出")
            sys.exit(0)

if __name__ == "__main__":
    main()