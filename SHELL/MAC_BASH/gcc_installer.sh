#!/bin/bash

# 设置 GCC 版本、安装前缀、要编译的语言。
VERSION="master-wip-apple-si"  # 这个版本号可能需要定期更新，以获取最新的 GCC 开发分支
PREFIX="/opt/gcc/gcc-${VERSION}"
LANGUAGES="c,c++,fortran"
# 使用 getconf 获取 CPU 核心数, macOS 上使用 sysctl。  使用 $() 包裹命令可移植性更强。
MAKE="make -j$(getconf _NPROCESSORS_ONLN 2>/dev/null || sysctl -n hw.ncpu)"
sysroot=$(xcrun --show-sdk-path)

# 临时目录，用于下载和构建 GCC
temp_gcc="${PREFIX}/temp-gcc"

# 函数：通过 brew 获取软件包的安装路径 (更具可读性的写法)
brew_path() {
  brew --prefix "$1"
}

# 获取当前机器架构
MACHINE_ARCH=$(uname -m)
echo "Detected architecture: ${MACHINE_ARCH}"

# 根据架构设置默认配置选项
CONFIGURE_OPTIONS=(
  --prefix="${PREFIX}"
  --build="aarch64-apple-darwin$(uname -r | awk -F. '{print $1}')"
  --enable-languages="${LANGUAGES}"
  --with-sysroot="$sysroot"
  --with-gmp="$(brew_path gmp)"
  --with-mpfr="$(brew_path mpfr)"
  --with-mpc="$(brew_path libmpc)"
  --with-isl="$(brew_path isl)"
  --with-zstd="$(brew_path zstd)"
  --with-libintl-prefix="$(brew --prefix gettext)"
  --enable-multilingual
  --enable-nls
  --with-system-zlib
  --enable-shared
  # --disable-bootstrap  #  如果构建速度过慢，可以取消注释此行以禁用自举编译（但可能会降低优化级别）
)

# 检查并安装依赖 (使用 brew), 明确检查 gettext
for pkg in gmp mpfr libmpc gettext; do
  if ! brew list "${pkg}" &> /dev/null; then
    echo "正在安装 ${pkg}..."
    brew install "${pkg}"
  fi
done
# 确保 gettext 的 include 目录被添加到 CPATH 中 (有时需要)
# 使用 := 确保只在 CPATH 未定义时设置，避免重复添加。
: "${CPATH:=$(brew --prefix gettext)/include}"
export CPATH

# 检查 make 命令是否存在
if ! command -v make &> /dev/null; then
  echo "错误：未找到 make 命令。请先安装 make。"
  exit 1
fi

# 目录检查和创建, 简化逻辑
if [ ! -d /opt/gcc ]; then
    echo "需要 sudo 权限创建 /opt/gcc"
    sudo mkdir -p /opt/gcc
    sudo chown "$(whoami)":admin /opt/gcc
fi

mkdir -p "${PREFIX}"  # 总是创建 PREFIX 目录
if [[ ! -w "${PREFIX}" ]]; then
    echo "需要 sudo 权限修改 ${PREFIX}"
    sudo chown "$(whoami)":admin "${PREFIX}"
fi

mkdir -p "${temp_gcc}" # 总是创建临时目录

cd "${temp_gcc}" || exit 1

# 询问用户选择下载方式 (只有在 temp_gcc/gcc 不存在时才询问)
if [[ ! -d "gcc" ]]; then  # 只检查 gcc 目录
  while true; do
    read -rp "选择下载方式 (1: git, 2: wget): " choice
    case "${choice}" in
      1)
        DOWNLOAD_METHOD="git"
        GCC_REPO="https://github.com/iains/gcc-darwin-arm64"
        break
        ;;
      2)
        DOWNLOAD_METHOD="wget"
        # 对于 wget 方式，由于我们使用的是 master-wip-apple-si 分支，
        #  GNU FTP 上没有对应的 tar.gz 文件。所以这里需要特别处理。
        #  要么提供一个可用的 tar.gz 下载链接（如果有的话），
        #  要么回退到 git 方式。这里改为提示用户并回退到 git。
        echo "wget 方式不支持 master-wip-apple-si 分支。请选择 git 方式。"
        DOWNLOAD_METHOD="git"
        GCC_REPO="https://github.com/iains/gcc-darwin-arm64"
        break
        ;;
      *)
        echo "无效选择。请输入 1 或 2。"
        ;;
    esac
  done
fi

# 下载 GCC 源码
if [[ "${DOWNLOAD_METHOD}" == "git" ]]; then
  # 直接克隆 master-wip-apple-si 分支
  if [[ ! -d "gcc" ]]; then
    git clone --depth 1 --branch "master-wip-apple-si" "${GCC_REPO}" "gcc"
  fi
elif [[ "${DOWNLOAD_METHOD}" == "wget" ]]; then
  #  因为上面已经处理了 wget 不可用的情况，这里可以省略。但为了完整性，保留一个错误提示。
  echo "错误：wget 方式不支持当前分支。请使用 git 方式。"
  exit 1
fi

cd "gcc" || exit 1
BUILD_DIR="./build"  # 使用相对路径, 因为我们总是克隆到 gcc 目录

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}" || exit 1

# 配置 GCC
if [[ -f Makefile ]]; then
  make clean
fi

# 使用 ../configure，因为我们在 build 目录中
../configure "${CONFIGURE_OPTIONS[@]}" 2>&1 | tee configure.log

if [[ $? -ne 0 ]]; then
  echo "错误：configure 失败。请查看 configure.log 文件获取详细信息。"
  exit 1
fi

# 构建 GCC
${MAKE} 2>&1 | tee make.log

if [[ $? -ne 0 ]]; then
  echo "错误：make 失败。请查看 make.log 文件获取详细信息。"
  exit 1
fi

# 安装 GCC
sudo ${MAKE} install 2>&1 | tee make_install.log

if [[ $? -ne 0 ]]; then
  echo "错误：make install 失败。请查看 make_install.log 文件获取详细信息。"
  exit 1
fi

echo "GCC 安装完成。请将以下内容添加到您的 shell 配置文件 (例如 ~/.bashrc 或 ~/.zshrc):"
echo "export PATH=\"${PREFIX}/bin:${PATH}\""
echo "export LD_LIBRARY_PATH=\"${PREFIX}/lib:${LD_LIBRARY_PATH}\"" #  更常用的写法
echo 'export LANG="zh_CN.UTF-8"'        # 这些通常不需要设置，除非有特殊需求。
echo 'export LANGUAGE="zh_CN.UTF-8"'     #  本地化通常由系统设置控制。
echo "export LC_MESSAGES=\"${PREFIX}/share/locale\""
