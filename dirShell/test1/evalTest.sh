#!/usr/sh

touch test.txt
echo -e "hello world..... \nthis is freedom world.\n123" > test.txt
#cat test.txt

eval echo \$$#

pipe="|"
eval ls ${pipe} wc -l

x=100
ptrx=x
echo $x
eval echo \$$ptrx

#rm -rf test.txt
echo "Done"
