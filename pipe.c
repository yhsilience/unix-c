#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void )
{
        int fd[2];
        pipe(fd); // 初始化管道
        int pid = fork();
        if(pid>0) //父进程
        {
          close(fd[0]); // 关掉　读端
          int i;
          for(i=100;i<=120;i++)
          {
            write(fd[1],&i,sizeof(int));
            sleep(1);
          }
          close(fd[1]);
          exit(0);
        }
        close(fd[1]); // 关掉写端
        int x = 0;
        int i ;
        for(i=0;i<=20;i++)
        {
          read(fd[0],&x,sizeof(int));
          printf("%d\n",x);
          fflush(stdout);
        }
        close(fd[0]);
}
