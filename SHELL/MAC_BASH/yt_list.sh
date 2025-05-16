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
yt-dlp -f 'bv*[height<=1080]+ba/b[height<=1080] / bv*+ba/b' --download-archive videos.txt "$playlist_url" -o '%(channel_id)s/%(playlist_id)s/%(title)s_%(id)s.%(ext)s' --cookies-from-browser chrome 
yt-dlp --skip-download --write-subs --sub-langs en,zh.* --convert-subs srt -o '%(channel_id)s/%(playlist_id)s/%(title)s_%(id)s.%(ext)s' "$playlist_url" --cookies-from-browser chrome


# 带字幕
# yt-dlp -f 'bv*[height<=1080]+ba/b[height<=1080] / bv*+ba/b' --download-archive videos.txt "$playlist_url" -o '%(channel_id)s/%(playlist_id)s/%(title)s_%(id)s.%(ext)s' --cookies-from-browser chrome --write-subs --sub-langs en,zh.* --convert-subs srt


# 可能更好的选择(但不是list)
# yt-dlp -k --write-subs --sub-langs &#34;en&#34; --convert-subs srt $playlist_url

# Skip版本
# yt-dlp --skip-download --write-auto-subs --sub-langs &#34;zh-Hans-en&#34; --convert-sub srt




