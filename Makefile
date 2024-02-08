MODULE_NAME=simple-printer
obj-m += $(MODULE_NAME).o
 
PWD := $(CURDIR)
 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	cd user-space && make

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	cd user-space && make clean
	
load:
	sudo insmod $(MODULE_NAME).ko
	
unload:
	sudo rmmod $(MODULE_NAME)

