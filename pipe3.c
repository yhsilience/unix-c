#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main (void)
{
        /*打开管道*/
        int fd = open("pipe_file" ,O_RDONLY);
        if(fd ==-1) {
                perror("pipe_file open failed");
                exit(-1);
        }
        /*进行读写*/
        int x,i;
        for(i=0; i<9; i++) {
                read(fd,&x,sizeof(int));
                printf("%d\n",x);
                fflush(stdout);
        }
        /*关闭管道*/
        close(fd);
}
