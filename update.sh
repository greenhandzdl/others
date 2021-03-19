#! /bin/bash

echo start

git pull
git add .

read -p "输入commit: "  commit

git commit -m "$commit"
git push

echo end
