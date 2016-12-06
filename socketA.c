#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void)
{
        /*创建Socket描述符*/
        int sd = socket(PF_UNIX,SOCK_DGRAM,0);
        if(sd == -1)
        {
                printf("socket 创建失败\n");
                return -1;
        }
        /*准备通信地址*/
        struct sockaddr_un addr; //本地通信地址
        memset(&addr,0,sizeof(addr));
        addr.sun_family = PF_LOCAL;
        strcpy(addr.sun_path,"192.168.154.128");
        /*将Socket描述符和通信地址绑定*/
        int res = bind(sd,(const struct sockaddr *)&addr,sizeof(addr)); // P486
        if(res == -1)
        {
                printf("绑定地址失败\n");
                return -1;
        }
        /*
           *进行通信
         *  read/write socket作为文件
         *  send/recv
         *  sendto/recvfrom 有目标的发送
         *  sendmsg/recvmsg 发送和接收都是消息结构
         */
        printf("等待数据接收。。。。。。\n");
        char buf[1024]={};
        while(1)
        {
                memset(buf,0,sizeof(buf));
                read(sd,buf,sizeof(buf));
                printf("收到数据：%s\n",buf);
        }
        /*关闭Socket，释放资源*/
        close(sd);
}
