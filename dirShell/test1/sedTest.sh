#!/usr/sh

touch test.txt
echo "=========="
echo -e "hello world..... \n this is freedom world.\n 123ID Name PHP Linux MySQL Average\n1 Liming 82 95 86 87.66\n1 Liming 82 95 86 87.66\n2 Sc 74 96 87 85.66\n3 Gao 99 83 93 91.66" > test.txt
echo "=========="
cat test.txt
echo "=========="

sed '2p' test.txt
echo "=========="
sed -n '2p' test.txt
echo "=========="
sed -n '2,4p' test.txt
echo "=========="
#sed '2,4d' test.txt
echo "=========="
sed '4a hello' test.txt
echo "=========="
sed '4i hello > world' test.txt
echo "=========="

sed -n'2i hello \
world' test.txt

echo "=========="
cat test.txt
echo "=========="
cat test.txt | sed '2c No such person'
echo "=========="
sed -i'2c No such person' test.txt
echo "=========="
sed '3s/74/99/g' test.txt
echo "=========="
sed '4s/^/#/g' test.txt
echo "=========="
sed -e 's/Liming//g; s/Gao//g' student.txt

echo "=========="
cat test.txt
echo "=========="
#rm -rf test.txt
echo "Done"