#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void alarm_sig(int signo)
{
        printf("捕获到信号%d\n",signo );
        printf("时间到了\n");
        return 0;
}
int main()
{
        signal(SIGALRM,alarm_sig);
        alarm(5);
        sleep(3);
        /*重置计数器，并返回上次计数器的值*/
        int ret = alarm(10);
        printf("计时器还有%d时间停止\n",ret);
        pause();
}
