#!/bin/sh

DATE=$(date)
#echo "$DATE"

git add .
git commit -m "[UPDATE:bulb:] $DATE"
git push
