#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main (void)
{
        printf("程序开始运行\n");
        fork();
        printf("其中一个进程运行\n");
        while (1) ;
}
