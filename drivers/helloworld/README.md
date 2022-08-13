## 编译

直接执行make即可编译生成helloworld.ko 驱动文件


make clean删掉编译文件



## 加载卸载驱动


insmod helloworld.ko

rmmod helloworld

## 查看打印信息

dmesg

```text
[449805.499709] helloworld: loading out-of-tree module taints kernel.
[449805.684387] helloworld: module verification failed: signature and/or required key missing - tainting kernel
[449806.288129] hello world!
[449817.249157] byebye!
```
