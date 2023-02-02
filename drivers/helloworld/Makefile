KERNELDIR := /usr/src/kernels/$(shell uname -r)
CURRENT_PATH := $(shell pwd)

obj-m := helloworld.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build  M=$(CURRENT_PATH) modules
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(CURRENT_PATH) clean
