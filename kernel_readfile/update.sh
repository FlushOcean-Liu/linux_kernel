#cp build/bid_ucache.ko /lib/modules/3.10.0-1160.71.1.el7.x86_64/
echo "start to rmmod read_file ..."
result=$(rmmod read_file)
echo $result
#modprobe bid_ucache
echo "start to inmod read_file ..."
insmod read_file.ko
