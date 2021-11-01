#!/bin/sh
DRIVER="testDriver"

echo $DRIVER
#unset DRIVER
#echo $DRIVER

DRIVER2='TEST2'
str="helloworld \"$DRIVER2\""
#str="helloworld \"${DRIVER2}\"\r\n"
echo $str $DRIVER
echo ${#DRIVER} ${#str}

#str2=${str:1:4} #bash
#echo $str2

#currentDir=$(readlink -f "$(dirname "$0")")
#echo $currentDir
currentDir=$(dirname "$(readlink -f "$0")")
echo $currentDir
#echo \`currentDir`\
#echo `echo `date +%Y-%m-%d``
echo $(echo $(date +%Y-%m-%d))
echo $(date +%Y-%m-%d)

a=b
echo $ab
echo ${a}bash

#a=$(hostname)
#b=${a:3:3}
#APP=$(echo ${b})

Test_Name=kevin/bo/AnHui
echo ${Test_Name}
Test_Path=${Test_Name////.}
echo ${Test_Path}

Test_Path=${Test_Path/.//}
echo ${Test_Path}

Test_Path=$(echo $Test_Path | tr '[a-z]' '[A-Z]')
echo ${Test_Path}

echo "hello world" |tr -t [:lower:] [:upper:]
echo "HELLO WORLD" |tr -t [:upper:] [:lower:]

array_name=(value0 value1 value2 value3)
echo ${array_name}

array_name2=(
value0
value1
value2
value3
)

echo ${array_name2}

lengthn=${#array_name[n]}
echo ${lengthn}

:<<EOF
注释内容...
注释内容...
注释内容...
EOF
:<<!
注释内容...
注释内容...
注释内容...
!

:<<EOF
:<<'
注释内容...
注释内容...
注释内容...
'
EOF

#enable_cfg80211=`ls |grep "qcacfg80211.config.enable='0'"`
enable_cfg80211=`df -lh`
echo ${enable_cfg80211}
[ -n "${enable_cfg80211}" ] && echo ${enable_cfg80211}

function Hello()
{
        local text="Hello World!!!" #局部变量
        echo $text
}

Hello

ker_ver=`uname -r |cut -d. -f1`
echo $ker_ver

#:<<EOF
echo $(cat /sys/class/net/ens33/address)
cat <<EOF
hello
option --->>>
EOF

macaddr_add() {
	local mac=$1
	local val=$2
	local oui=${mac%:*:*:*} #Delete LEFT :xx:xx:xx
	local nic=${mac#*:*:*:} #Delete RIGHT xx:xx:xx:

	nic=$(printf "%06x" $((0x${nic//:/} + $val & 0xffffff)) | sed 's/^\(.\{2\}\)\(.\{2\}\)\(.\{2\}\)/\1:\2:\3/')
	echo $oui:$nic
}

#local base_mac=$(ritool get MACAddress | awk '{print $2}')
base_mac="00:86:12:86:44:80"
wifi0_mac_add=10
wifi1_mac_add=9
mac_address=$(macaddr_add $base_mac $wifi0_mac_add)
echo ${mac_address}

:<<EOF
mac_address=$(macaddr_add $base_mac $wifi1_mac_add)
echo ${mac_address}
EOF

default_channel=
if [ ! -z ${default_channel} ]; then
    echo 1 ${default_channel}
fi

if [ -n "${default_channel}" ]; then
    echo 2 ${default_channel}
fi

touch address
mac_address=$(cat ./address)
mac_address=$(macaddr_add $base_mac $wifi1_mac_add)
cat <<EOF
JUST CAT    ${mac_address}
EOF


valuetest0="123"
if [ -n "$valuetest0" ]
then
	echo "valuetest0 is good "$valuetest0""
else
	echo "sizeof valuetest0 is 0"
fi