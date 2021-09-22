PWD = $(shell pwd)  
KERNEL_SRC = /lib/modules/4.15.0-142-generic/build

obj-m := hello.o  
module-objs := hello.o  

all:  
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules  


clean:  
	rm *.ko  
	rm *.o
	rm *.mod.c
	#rm *.mod.o
	rm *.order
	rm *.symvers