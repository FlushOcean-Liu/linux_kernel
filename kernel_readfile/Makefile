CURRENT_PATH := $(shell pwd)

obj-m := read_file.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build  M=$(CURRENT_PATH) modules
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(CURRENT_PATH) clean

