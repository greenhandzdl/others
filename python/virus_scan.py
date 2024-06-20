# 作者：greenhandzdl
# 使用说明：利用clamav多进程扫描全盘（建议：使用单独的文件夹方便查看日志）

import os
import subprocess
import concurrent.futures
import psutil
from tqdm import tqdm
import time
import threading
import logging

# 要扫描的目录列表
directories = [
    "bin", "dev", "home", "lib64", "opt", "root", "sbin", ".snapshots",
    "sys", "usr", "boot", "etc", "lib", "mnt", "proc", "run", "snap", "srv",
    "tmp", "var"
]

base_path = "/"
clamav_cmd = "clamscan"
update_cmd = "freshclam"

# 设置日志记录
logging.basicConfig(filename='scan.log', level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def update_virus_database():
    print("正在更新病毒数据库...")
    logging.info("正在更新病毒数据库...")
    result = subprocess.run([update_cmd], capture_output=True, text=True)
    if result.stdout:
        print(result.stdout)
        logging.info(result.stdout)
    if result.stderr:
        print(f"更新时发生错误: {result.stderr}")
        logging.error(f"更新时发生错误: {result.stderr}")
    if result.returncode != 0:
        print("尝试使用 sudo 运行 freshclam...")
        result = subprocess.run(['sudo', update_cmd], capture_output=True, text=True)
        if result.stdout:
            print(result.stdout)
            logging.info(result.stdout)
        if result.stderr:
            print(f"使用 sudo 更新时发生错误: {result.stderr}")
            logging.error(f"使用 sudo 更新时发生错误: {result.stderr}")
    print("病毒数据库更新完成。")
    logging.info("病毒数据库更新完成。")

def scan_directory(directory, progress_bar):
    path = os.path.join(base_path, directory)
    log_file = f"{directory}_scan.log"
    start_time = time.time()

    try:
        result = subprocess.run([clamav_cmd, "-r", "--remove", path, "--log", log_file], capture_output=True, text=True)
        progress_bar.set_description(f"正在扫描 {directory}")
        logging.info(f"开始扫描 {directory}")
        
        # 解析日志文件以获取进度信息
        with open(log_file, 'r') as log:
            lines = log.readlines()
            total_files = len(lines)
            for i, line in enumerate(lines):
                progress_bar.set_description(f"正在扫描 {directory} ({i+1}/{total_files})")
                time.sleep(0.01)  # 模拟读取和处理日志文件的延迟

        if result.stderr:
            print(f"扫描 {directory} 时发生错误: {result.stderr}")
            logging.error(f"扫描 {directory} 时发生错误: {result.stderr}")
    
    except Exception as e:
        print(f"扫描 {path} 时发生异常: {e}")
        logging.error(f"扫描 {path} 时发生异常: {e}")
    finally:
        progress_bar.update(1)
        end_time = time.time()
        logging.info(f"扫描 {directory} 完成，用时 {end_time - start_time} 秒")

def display_system_usage(stop_event):
    while not stop_event.is_set():
        cpu_usage = psutil.cpu_percent(interval=1)
        memory_info = psutil.virtual_memory()
        memory_usage = memory_info.percent
        print(f"\rCPU 使用率: {cpu_usage}% | 内存使用率: {memory_usage}%", end="")
        logging.info(f"CPU 使用率: {cpu_usage}% | 内存使用率: {memory_usage}%")
        time.sleep(1)

def main():
    # 更新病毒库
    update_virus_database()

    # 创建用于停止系统监控线程的事件
    stop_event = threading.Event()

    # 使用 ThreadPoolExecutor 实现多线程
    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = []
        progress_bar = tqdm(total=len(directories))
        
        for directory in directories:
            futures.append(executor.submit(scan_directory, directory, progress_bar))
        
        system_monitor_thread = executor.submit(display_system_usage, stop_event)
        
        for future in concurrent.futures.as_completed(futures):
            try:
                future.result()
            except Exception as exc:
                print(f"扫描时发生异常: {exc}")
                logging.error(f"扫描时发生异常: {exc}")
        
        # 停止系统监控线程
        stop_event.set()
        system_monitor_thread.result()  # 确保系统监控线程退出
        progress_bar.close()
    
    print("\n扫描完成。")
    logging.info("扫描完成。")

if __name__ == "__main__":
    main()
