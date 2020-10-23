#! /bin/bash

echo start

git pull
git add .
git commit -m "update"
git push

echo end
