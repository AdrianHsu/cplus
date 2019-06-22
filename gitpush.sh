#!/bin/sh

DATE=$(date)
echo "$DATE"
git add .
git commit -m "$DATE"
git push
