obj-m := simplemodule.o

build:all
all:
	make -C /lib/modules/$(uname -r)/build M=$PWD modules
.PHONY:clean
clean:
	rm -rf *.ko *.o *.mod* *.order .cache.mk .simplemodule.* .tmp* Module.symvers
