#include <stdio.h>
#include <pthread.h>

char store[8];
int size=0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void print()
{
        int i;
        for(i=0; i<size; i++)
        {
                printf("%c",store[i]);
        }
        printf("\n");
}

void* producer(void *p)
{
        char c;
        printf("producer is run\n");
        for(c = 'A'; c<="Z"; c++)
        {
                pthread_mutex_lock(&lock); //对条件变量加锁
                while (size == 3)
                {
                        printf("full条件满足\n");
                        pthread_cond_wait(&full,&lock);
                        printf("不知道会不会运行到这里\n");
                }
                store[size] =c;
                printf("PUSH:%c\n",c);
                sleep(1);
                size++;
                print();
                pthread_cond_broadcast(&empty);
                pthread_mutex_unlock(&lock);
        }
}
void* customer(void *p)
{
        int i;
        printf("customer is run\n");
        for(i=0; i<52; i++)
        {
                pthread_mutex_lock(&lock);

                while(size == 0)
                {
                        pthread_cond_wait(&empty,&lock);
                }
                size--;
                printf("POP:%c\n",store[size]);
                print();

                pthread_cond_broadcast(&full);
                pthread_mutex_unlock(&lock);
        }
}


int main()
{
        pthread_t full_thread,empty_thread;

        pthread_create(&full_thread,0,&producer,0);
        pthread_create(&empty_thread,0,&customer,0);

        pthread_join(&full_thread,0);
        pthread_join(&empty_thread,0);

}
