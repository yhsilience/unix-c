#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sig_quit(int signo)
{
        printf("捕获到信号%d\n",signo);

}
int main()
{
        sigset_t new,old,pend;
        if(signal(SIGQUIT,sig_quit) == SIG_ERR)
        {
                printf("signal failed\n");
                return 0;
        }
        if(signal(SIGINT,sig_quit) == SIG_ERR)
        {
                printf("signal failed\n");
                return 0;
        }
        sigemptyset(&new);
        sigemptyset(&old);
        sigemptyset(&pend);

        sigaddset(&new,SIGQUIT);
        sigaddset(&new,SIGINT);
        sigprocmask(SIG_SETMASK,&new,&old); //

        sigemptyset(&new);
        sigaddset(&new,SIGALRM);
        sigprocmask(SIG_BLOCK,&new,NULL);


        sigemptyset(&new);
        sigaddset(&new,SIGINT);
        sigprocmask(SIG_UNBLOCK,&new,NULL);


        printf("信号已经屏蔽\n");
        printf("发送 Ctrl c 或者 Ctrl \\ \n");

        sleep(6);

        sigpending(&pend);
        if(sigismember(&pend,SIGQUIT)) printf("信号SIGQUIT来过\n");
        if(sigismember(&pend,SIGINT)) printf("信号SIGINT来过\n");

        sigprocmask(SIG_SETMASK,&old,NULL);

        printf("信号屏蔽已经恢复\n");
        printf("发送 Ctrl c 或者 Ctrl \\\n");
        sleep(10);
}
