## 1.netlink功能  
主要用于内核态与用户态进行数据通信

## 2.编译执行
make  
insmod netlink_kernel.ko

dmesg查看内核打印信息

执行用户态程序，输入发送数据
./netlink_user

注意要先insmod netlink_kernel.ko在执行netlink_user
