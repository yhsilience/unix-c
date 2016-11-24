#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
        pid_t pid1,pid2;
        pid1 = fork();
        if(pid1 > 0)
                pid2 = fork();
        if(pid1 == 0)
        {
                printf("子进程1=%d开始运行\n",getpid());
                sleep(5);
                printf("子进程1运行结束\n");
                return 0;
        }
        if(pid2 == 0)
        {
                printf("子进程2=%d开始运行\n",getpid());
                while(1) ;
                printf("子进程2运行结束\n");
                return 0;
        }
        printf("父进程结束\n");
        printf("父进程等待进程%d\n",pid1);
        waitpid(pid1,NULL,0);
        waitpid(pid2,NULL,0);
        printf("父进程结束\n");

}
