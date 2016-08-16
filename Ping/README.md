由于创建ICMP套接字需要root权限，所以在编译时，切换到root用户，执行make命令。
然后用chmod u+x main 命令将生成的可执行程序（main）的有效用户id设置为root的id，使其运行时具有root权限。
