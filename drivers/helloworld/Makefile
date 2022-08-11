#KERNELDIR := /home/sixer/imx_kernel/linux-imx-rel_imx_4.1.15_2.1.0_ga
KERNELDIR := /data/opensource/linux-5.0.1
CURRENT_PATH := $(shell pwd)

#export ARCH=arm
#export CROSS_COMPILE=arm-linux-gnueabihf-

target := helloworld
obj-m := $(target).o
APP_NAME := $(target)_app

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean

dir_exist = $(shell if [ -d "/nfsroot/$(target)/" ]; then echo "exist"; else echo "noexist"; fi)
$(info $(dir_exist))

install:
ifeq ("$(dir_exist)", "noexist")
    $(shell mkdir /nfsroot/$(target))
    #"文件夹不存在，已重新创建文件夹"
endif
#cp *.ko  /nfsroot/$(target)/
