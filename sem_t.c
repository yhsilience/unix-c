#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/*临界资源*/
char* names[5];
int size =0;

/*定义锁(信号量)*/
sem_t lock;
void* thread1(void* arg)
{
        printf("thread1 is run\n");
        /*临界区*/
        sem_wait(&lock);  // 加锁

        names[1]= "小白";
        printf("%s\n",names[1]);
        sleep(1);
        sem_post(&lock);

}
void* thread2(void* arg)
{
        printf("thread2 is run\n");
        sem_wait(&lock); // 加锁
        names[2]= "小黑";
        printf("%s\n",names[2]);
        sleep(1);

}
int main()
{
        pthread_t t1,t2,t3;
        int i=0;
        sem_init(&lock,0,1);
        pthread_create(&t1,0, &thread1,0);
        pthread_create(&t2,0, &thread2,0);
        pthread_join(&t1,0);
        pthread_join(&t2,0);
        printf("************\n");
        sem_post(&lock);

}
