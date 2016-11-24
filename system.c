#include<stdio.h>
#include<stdlib.h>

int main(void)
{
  printf("程序开始运行\n");
  system("ls -l /home/yh"); // fork() ---> exec() -----> waitpid();
  printf("程序运行结束\n");
}
