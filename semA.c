#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>

int semid;
void quit(int signo)
{
        printf("删除信号量集\n");
        semctl(semid,IPC_RMID,0,0); // 删除信号量集
        signal(signo,SIG_DFL); //恢复默认信号操作
        return 0;
}

int main()
{
        /*生成key*/
        key_t key = ftok(".",100);
        /*创建信号量集*/
        semid = semget(key,
                       1, // 信号量数
                       IPC_CREAT|IPC_EXCL|0666);
        if(semid  == -1)
        {
                printf("sem create failed \n");
                return -1;
        }
        /*初始化信号量的值*/
        int res;
        res = semctl(semid,
                     0, //信号量下标
                     SETVAL, //
                     2); //信号量的值为2
        if(res == -1)
        {
                printf("init semval failed\n");
                return -1;
        }
        /*操作信号量*/
        struct sembuf op;
        op.sem_num = 0; /*要操作的信号量的下标*/
        op.sem_op = -1; /*对信号量进行何种操作(加减)*/
        op.sem_flg = 0; /*标志值，可以为IPC_NOWAIT*/
        printf("Ctrl+c 退出\n");
        signal(SIGINT,quit);
        while(1)
        {
                printf("开始获取共享资源\n");
                if(semop(semid,&op,1))
                {
                        printf("获取资源成功\n");
                }
                sleep(1);
        }
}
