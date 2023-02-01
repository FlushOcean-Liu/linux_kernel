MODULE_NAME :=netlink_kernel
obj-m :=$(MODULE_NAME).o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
	gcc -o netlink_user netlink_user.c 
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -f netlink_user

