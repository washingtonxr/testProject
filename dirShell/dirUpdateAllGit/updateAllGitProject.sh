#!/bin/bash

REPODB_FILE="gitRepo.txt"

echo "List all git project."
rm -rf $REPODB_FILE
find ../../ -name ".git" >> $REPODB_FILE
cat $REPODB_FILE | while read line
do
    projectPath=$(echo $line | sed -e 's/\.git//g')
    echo "Update this project, path:$projectPath"
    cd $projectPath
    echo "pwd >>"
    pwd
    git pull
    cd -
    echo "pwd >>"
    pwd
done

rm -rf $REPODB_FILE

echo "Update done."
echo "Exit"
