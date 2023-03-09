diff -uprN linux-0.11/ linux-0.11_new  > linux.patch


# 生成补丁
diff -uprN raw.txt new.txt  > linux.patch


# 打补丁，在原版目录下执行打补丁命令，-p后面代表忽略哪一级路径
patch -p0 < linux.patch


# 卸载补丁，还原打补丁之前的状态
patch -p0 -R < linux.patch

