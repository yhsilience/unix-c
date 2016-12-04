#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

int  main (void)
{
        /*创建管道文件*/
        if(mkfifo("pipe_file",0777)<0) {
                perror("pipe file create failed");
                exit(-1);
        }
        printf("pipe_file is created successed\n");
        /*打开管道*/
        int fd = open("pipe_file",O_WRONLY);
        printf("fd = %d\n",fd);
        if(fd ==-1) {
                perror("pipe open failed");
                exit (-1);
        }
        printf("pipe_file open  success\n");
        /*开始读写*/
        int i;
        for(i=0; i<10; i++) {
                write(fd,&i,sizeof(int));
                printf("%d\n",i);
                sleep(1);
        }
        /*关闭管道*/
        close(fd);
        /*删除管道文件*/
        unlink("pipe_file");

}
