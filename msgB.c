#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
  /*生成key*/
  key_t key=ftok(".",100);
  /*创建消息队列*/
  int msgid = msgget(key,0);
  if(msgid == -1)
  {
    printf("创建失败\n");
    return -1;
  }
  /*发送和接受消息*/
  char buf1[200] ={};
  char buf2[200] ={};
  int res= msgrcv(msgid,buf1,sizeof(buf1),0,MSG_NOERROR);
  res= msgrcv(msgid,buf2,sizeof(buf2),0,MSG_NOERROR);
  if(res == -1)
  {
    printf("msg send failed\n");

  }
  printf("MESSAGE1:%s\n",buf1);
  printf("MESSAGE2:%s\n",buf2);
  /*删除消息队列*/
  msgctl(msgid,IPC_RMID,0);
}
