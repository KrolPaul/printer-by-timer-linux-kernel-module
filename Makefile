MODULE_NAME=simple-printer
obj-m += $(MODULE_NAME).o

PWD = $(CURDIR)

# Define macro for module helpers (module directory)
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MODULE_DIR := $(dir $(MKFILE_PATH))
EXTRA_CFLAGS := -D MODULE_DIR=\"$(MODULE_DIR)\"

# Load module params
-include $(PWD)/config.mk
MODULE_PARAMS = file_name=$(file_name) print_every_n_sec=$(print_every_n_sec)
 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	cd helper && make

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	cd helper && make clean
	
load:
	sudo insmod $(MODULE_NAME).ko $(MODULE_PARAMS)
	
unload:
	sudo rmmod $(MODULE_NAME)

