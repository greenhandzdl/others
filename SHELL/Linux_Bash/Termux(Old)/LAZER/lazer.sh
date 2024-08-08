#! /bin/
echo -ne "\033]lazer.sh\077"&&clear
echo 作者:Greenhandzdl
echo version:2022.01.22
echo 网站:https://greenhandzdl.github.io
echo 该程序不具备自主更新能力,请自行决定是否更新
echo 正在初始化...loading
echo 　　　　　　 ＿＿
echo 　　　　　／＞　　フ
echo 　　　　　|  　_　 _ l
echo 　 　　　／` ミ＿xノ
echo 　　 　 /　　　 　 |
echo 　　　 /　 ヽ　　 ﾉ
echo 　 　 │　　|　|　|
echo 　／￣|　　 |　|　|
echo 　| (￣ヽ＿_ヽ_)__)
echo 　＼二つ
cp lazer.sh $HOME/lazer_20220122.sh
echo 初始化成功
echo 系统环境//screenfetch && screenfetch && echo 网络状态: && ifconfig && echo 端口开放情况//nmap && nmap 127.0.0.1 && echo 运行时间: && date && echo 一言: && fortune
echo 懒人快捷:
echo 选项1:更新
echo tips:环境termux
echo 选项2:运行nginx网站//第一次
echo tips:请自先备好nginx php-fpm mysql
echo 选项3:清理.生成.推上去.备份--hexo网站
echo tips:请事先把hexo文件放在$HOME下
echo 选项4:更新主题--hexo
echo tips:请事先把hexo文件放在$HOME下
echo 选项5:随机听,放松心情
echo tips:请事先把文件放在$HOME/daily/mpv下,请自行准备好mpv
echo tips:任何操作执行完都会回到$HOME

read -p "输入选项: "  choice
if [ $choice -eq 1 ];
 then
    echo 正在更新中...//如果失败请挂梯子重试
    apt update && apt upgrade && apt-get clean all
 fi
if [ $choice -eq 2 ];
 then
     echo 正在打开wordpress网站
     nginx
     php-fpm
     mysqld_safe
     echo 打开成功
   fi
if [ $choice -eq 3 ];
 then
   echo 即将开始
   cd $HOME/hexo
   hexo clean && hexo d -g && hexo b
   echo 注意:插件等导致问题请自行解决
   echo 这里仅执行hexo clean && hexo d -g && hexo b
 fi
if [ $choice -eq 4 ];
 then
  echo 暂不支持
 fi
if [ $choice -eq 5 ];
 then
  echo 即将播放...loading
  echo  本次播放:
  tree $HOME/daily/mpv
  mpv $HOME/daily/mpv --shuffle
 fi

cd $HOME
echo End...
echo 为表清白，看看历史吧 ｰ̀εｰ́ 
