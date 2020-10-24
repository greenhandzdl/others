#! /bin/bash
echo 作者:Greenhandzdl  helper:Q:157668997
echo version:20201024
echo Start...
echo 选项1适用于网络好的童鞋
echo 选项2适应于网络不好的童鞋
read -p "输入选项: " choice

if [ $choice -eq 1 ];
   then
     pkg install nodejs -y && npm install hexo && hexo init blog && cd blog && hexo g && hexo s
    fi

if [ $choice -eq 2 ];
   then
	npm config set registry http://registry.npm.taobao.org
        npm install hexo-cli -g
        git clone --depth 1 https://gitee.com/weilining/hexo-starter.git blog
        cd blog
        git clone --depth 1 https://gitee.com/weilining/hexo-theme-landscape.git themes/landscape
        npm i
        hexo server
     fi

echo End...
