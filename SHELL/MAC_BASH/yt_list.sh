#!/bin/bash

# 检查是否提供了参数
if [ -z "$1" ]; then
  echo "错误：未提供YouTube播放列表链接。"
  echo "使用方法：$0 <YouTube播放列表链接>"
  exit 1
fi

# 获取播放列表链接
playlist_url="$1"

# 使用yt-dlp下载播放列表
yt-dlp -f 'bv*[height<=1080]+ba/b[height<=1080] / bv*+ba/b' --download-archive videos.txt "$playlist_url" -o '%(channel_id)s/%(playlist_id)s/%(title)s_%(id)s.%(ext)s'
