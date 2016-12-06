#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


int main()
{
        key_t key = ftok(".",100);
        int semid = semget(key,0,0);
        if(semid == -1 )
        {
                printf("get sem failed\n");
                return -1;
        }
        struct sembuf op;
        op.sem_num = 0;
        op.sem_op = 1;
        op.sem_flg = 0;

        int i;
        for(i=0; i<3; i++)
        {
                semop(semid,&op,1);
        }
}
