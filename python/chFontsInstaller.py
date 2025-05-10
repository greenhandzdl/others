import subprocess

# 根据 Arch Wiki 原文修正的字体包列表
font_packages = [
    "adobe-source-han-sans-cn-fonts",    # 思源黑体（CN 版本）
    "adobe-source-han-serif-cn-fonts",  # 思源宋体（CN 版本）
    "noto-fonts-cjk",                   # Google Noto 字体（含中文）
    "wqy-microhei",                     # 文泉驿微米黑
    "wqy-microhei-lite",                # 文泉驿微米黑精简版
    "wqy-bitmapfont",                   # 文泉驿点阵宋体
    "wqy-zenhei",                       # 文泉驿正黑
    "ttf-arphic-ukai",                  # AR PL UKai（楷体）
    "ttf-arphic-uming",                 # AR PL UMing（明体）
]

def install_fonts():
    print("开始安装中文字体（基于 Arch Wiki 最新规范）...")
    for package in font_packages:
        try:
            subprocess.run(["yay", "-S", "--needed", "--noconfirm", package], check=True)
            print(f"✅ 已安装: {package}")
        except subprocess.CalledProcessError as e:
            print(f"❌ 安装失败: {package} (错误码: {e.returncode})")

if __name__ == "__main__":
    install_fonts()