#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void sig_int(int signo)
{
  printf("捕获信号%d\n",signo);
  sleep(10);
}
void sig_int_info(int signo, siginfo_t* info , void* p)
{
  printf("捕获到信号%d\n",signo);
  printf("信号是有进程%d\n",info->si_pid);
}
 int main()
 {
   struct sigaction action;
   memset(&action,0,sizeof(action));
   /*信号处理函数*/
  //action.sa_handler = sig_int;
   action.sa_sigaction = sig_int_info;
  /*信号处理时，屏蔽掉指定的信号集*/
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set,SIGQUIT);
  action.sa_mask =set;

  /*第一次调用信号处理函数的同时恢复该信号的默认处理方式*/
  action.sa_flags = SA_RESETHAND;
  /* SA_SIGINFO 可以让信号处理函数获得更详细的信息
  *  SA_NODEFER 让信号处理函数正在执行时，不屏蔽信号的到来
  */
  action.sa_flags = SA_SIGINFO | SA_NODEFER;
  sigaction(SIGINT,&action,NULL);
  while (1);
 }
