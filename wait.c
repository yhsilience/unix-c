#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
        pid_t pid = fork();
        if(pid > 0)
        {
                printf("父进程开始\n");
                int status;
                printf("父进程等待子进程结束\n");
                pid_t cpid= wait(&status);
                printf("进程%d结束，子进程的退出码是%d\n",cpid,status);

                if(WIFEXITED(status))
                {
                        printf("子进程正常结束\n");
                        printf("子进程的退出码是%d\n",WEXITSTATUS(status));
                }
                if(WIFSIGNALED(status))
                {
                        printf("子进程异常退出\n");
                        printf("终止子进程的信号是：%d\n",WTERMSIG(status));
                }
                printf("父进程结束\n");
                return 0;
        }
        printf("子进程开始运行，睡眠.....\n");
        printf("cpid = %d \n", getpid());
        sleep(3);
        //while (1);
        printf("子进程结束\n");
        return 0;
}
