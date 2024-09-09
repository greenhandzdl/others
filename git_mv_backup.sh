#!/bin/bash
#: 描述：用于将.目录下所有git文件备份操作（没有预先检测文件目录是否存在，谨慎使用）
cp $(ls | grep -v '^\.\{1,2\}'|grep 'git')  SHELL/git_collection 