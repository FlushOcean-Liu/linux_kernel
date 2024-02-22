## 编译

直接执行make即可编译生成sysfs_file.ko 驱动文件


make clean删掉编译文件



## 加载卸载驱动


insmod sysfs_file.ko

rmmod sysfs_file

## 查看结果

在目录/sys/kernel下会生成sysfs_file目录，里面有文件名my_attr

每次cat my_attr显示如下：
[17]Hello, world!
每次读取文件，序号会自增1
