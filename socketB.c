#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
/*
* 参见  Unix 高级编程 P475
*
*
*
*
*/
int main()
{
        /*创建socket*/
        int sd = socket(AF_UNIX, //确定通信的特性{AF_INET(IPV4英特网),AF_INET6(IPV6英特网),AF_UNIX(UNIX域),AF_UPSPEC()};
                        SOCK_DGRAM,//套接字类型{SOCK_DGRAM,SOCK_RAW,SOCK_SEQPACKET,SOCK_STREAM}
                        0);//通常为0；
        if(sd == -1)
        {
                printf("socket 创建失败\n");
                return -1;
        }
        /*准备通信地址*/
        struct sockaddr_un addr;
        memset(&addr,0,sizeof(addr));
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path,"192.168.154.128");
        /*联通到通信地址*/
        int res = connect(sd,(const struct sockaddr*)&addr,sizeof(addr)); // 连接
        if(res == -1)
        {
                printf("连接失败\n");
                return -1;
        }
        /*进行通信*/
        while(1)
        {
                write(sd,"嘿，小白，是个傻逼\n",strlen("嘿，小白，是个傻逼\n"));
                sleep(1);
        }
}
