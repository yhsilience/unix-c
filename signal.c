#include <stdio.h>
#include <signal.h>

void sig( int signo)
{
    printf("捕获到信号%d\n",signo);
    /*恢复signo信号的默认处理行为*/
    signal(signo,SIG_DFL);
    return 0;
}
int main()
{
  /*进程开始捕获信号SIGINT，如果有进程接受到此信号就调用sig函数*/
  if(signal(SIGINT,sig) == SIG_ERR)
  {
    perror("捕获信号SIGINT失败\n");
  }
  /*忽略信号SIGOUT*/
  if(signal(SIGQUIT,SIG_IGN) == SIG_ERR)
  {
    perror("忽略信号SIGOUT失败\n");
  }
  signal(SIGKILL,SIG_IGN);
  while(1)
  {
    sleep(1);
    printf("程序运行。。。。。\n");
  }
}
