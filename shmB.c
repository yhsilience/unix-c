#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
        /*生产key*/
        key_t key = ftok(".",100);
        if(key == -1)
        {
                printf("key创建失败\n");
                return -1;
        }
        int shmid = shmget(key,0,0);
        if(shmid == -1)
        {
                printf("获取失败\n");
                return -1;
        }
        void* p  = shmat(shmid,0,0);
        if(p == (void*)-1)
        {
                printf("挂载失败\n");
                return -1;
        }
        int* pi =p;
        int i;
        for(i=0; i<100; i++)
        {
                printf("%d\n",pi[i]);
        }
        shmdt(p);
}
