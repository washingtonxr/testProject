#!/bin/bash

echo "Duplicate severial files!"

for i in $(seq 1 16)
#for i in $(seq 1 $(ls|wc -l))
do 
echo $i; 
cat template.sh > shell0$i.sh; 
cat shell0$i.sh;
done

chmod +x *

echo "Done!"

