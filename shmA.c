#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
        /*生产KEY*/
        key_t key = ftok(".",100);
        if(key == -1)
        {
                printf("key产生失败\n");
                return -1;
        }
        /*创建共享内存段*/
        int shmid = shmget(key,4096,IPC_CREAT|IPC_EXCL|0666);
        if(shmid == -1)
        {
                printf("创建共享内存段失败\n");
                return -1;
        }
        /*挂载共享内存段*/
        void * p = shmat(shmid,0,0);
        if(p ==(void *)-1 )
        {
                printf("挂载失败\n");
                return -1;
        }
        /*使用共享内存段*/
        int *pi = p;
        int i;
        for(i=10; i<50; i++)
        {
                pi[i-10]=i;
        }
        /*卸载共享内存段*/
        shmdt(p);
}
