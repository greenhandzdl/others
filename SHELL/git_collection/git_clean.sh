#!/bin/bash
#: 描述：删除.下所有gitignore描述的文件
while IFS= read -r line; do
    if [ -n '$line' ]; then
        find . -iname '$line' -print | xargs rm -r
    fi
done <.gitignore