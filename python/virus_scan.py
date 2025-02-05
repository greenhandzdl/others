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
    "usr", "boot", "etc", "lib", "mnt", "run", "snap", "srv",
    "tmp", "var", "proc", "sys"
]

base_path = "/"
clamav_cmd = "clamscan"
update_cmd = "freshclam"
max_threads = 8  # 最大并行线程数，根据系统资源调整
max_retries = 3  # 扫描失败重试次数

# 设置日志记录
logging.basicConfig(filename='scan.log', level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def update_virus_database():
    print("正在更新病毒数据库...")
    logging.info("正在更新病毒数据库...")
    result = subprocess.run(['sudo', update_cmd], capture_output=True, text=True)
    if result.stdout:
        print(result.stdout)
        logging.info(result.stdout)
    if result.stderr:
        print(f"更新时发生错误: {result.stderr}")
        logging.error(f"更新时发生错误: {result.stderr}")
    if result.returncode != 0:
        print("病毒数据库更新失败。")
        logging.error("病毒数据库更新失败。")
    else:
        print("病毒数据库更新完成。")
        logging.info("病毒数据库更新完成。")

def scan_directory(directory, progress_bar, retry_count=0):
    path = os.path.join(base_path, directory)
    log_file = f"{directory}_scan.log"
    start_time = time.time()

    try:
        result = subprocess.run(['sudo', 'ionice', '-c', '3', clamav_cmd, "-r", "--remove=yes", path, "--log", log_file], capture_output=True, text=True)
        progress_bar.set_description(f"正在扫描 {directory}")
        logging.info(f"开始扫描 {directory}")

        if result.stdout:
            logging.info(result.stdout)
        if result.stderr:
            # 处理权限不足的警告
            if "Permission denied" in result.stderr:
                print(f"扫描 {directory} 时发生权限不足错误: {result.stderr}")
                logging.warning(f"扫描 {directory} 时发生权限不足错误: {result.stderr}")
            else:
                print(f"扫描 {directory} 时发生错误: {result.stderr}")
                logging.error(f"扫描 {directory} 时发生错误: {result.stderr}")

        # 修改日志文件权限
        subprocess.run(['sudo', 'chown', f'{os.getuid()}:{os.getgid()}', log_file])
        subprocess.run(['sudo', 'chmod', '777', log_file])  # 设置权限为777

        # 检查扫描结果并解析日志文件
        with open(log_file, 'r') as log:
            log_content = log.read()
            if "Infected files: 0" not in log_content:
                if "Not removed: 0" not in log_content:
                    not_removed_files = []
                    for line in log_content.split('\n'):
                        if "Not removed:" in line:
                            not_removed_files.append(line)
                    logging.warning(f"扫描 {directory} 发现未能删除的文件: {not_removed_files}")
                    print(f"扫描 {directory} 发现未能删除的文件: {not_removed_files}")

    except Exception as e:
        print(f"扫描 {path} 时发生异常: {e}")
        logging.error(f"扫描 {path} 时发生异常: {e}")
        if retry_count < max_retries:
            logging.info(f"重新尝试扫描 {directory}，第 {retry_count + 1} 次")
            scan_directory(directory, progress_bar, retry_count + 1)
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
    with concurrent.futures.ThreadPoolExecutor(max_workers=max_threads) as executor:
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