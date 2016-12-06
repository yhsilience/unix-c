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
  int msgid = msgget(key,IPC_CREAT|IPC_EXCL|0666);
  if(msgid == -1)
  {
    printf("创建失败\n");
    return -1;
  }
  /*发送和接受消息*/
  int res= msgsnd(msgid,"hello message",14,0);
  if(res == -1)
  {
    printf("msg send failed\n");

  }
  res = msgsnd(msgid,"xiaobai shi shabi",17,0);
  if(res == -1)
  {
    printf("msg2 send failed\n");

  }
  /*删除消息队列*/
  //msgctl(msgid,IPC_RMID,0);
}
