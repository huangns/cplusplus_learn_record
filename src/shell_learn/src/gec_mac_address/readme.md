1./sys/class/net/eth0/address 可以直接读，不同的网卡名字需要修改eth0
2.ifconfig | awk '$0 ~ /HWaddr/ { print $5 }'  // /sbin/ifconfig | grep HWaddr
3.C/C++ pragram
