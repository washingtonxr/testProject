#!/bin/bash
make -C /lib/modules/$(uname -r)/build M=$PWD modules

#ifneq ($(KERNELRELEASE),)
#obj-m := simplemodule.o
#else
#PWD := $(shell pwd)
#
# make -C /lib/modules/$(username -r)/build M=$PWD modules
# insmod ./simplemodule.ko
# rmmod simple module
# dmesg | tail
#
#build:all
#all:
#	gcc -C /lib/modules/$(username -r)/build M=$PWD modules
#.PHONY:clean
#clean:
#	rm -f *.ko *.o *.symvers *.cmd *.cmd.o
#endif


