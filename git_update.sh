#! /bin/bash

echo Start
echo This Is Git_Version.

echo Preparing Project Tree
echo > tree.txt # Create Project Tree
tree | tee -a tree.txt # Load Project Tree
# If it's reported error,please offer issues to us

echo Loading

# Git Mod
git pull
git add .

read -p "输入commit: "  commit
git commit -m "$commit"

echo Uploading.
git push

echo End

echo "If you're interested in this project,you can give a like and follow author:Greenhandzdl"
