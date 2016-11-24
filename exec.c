#include <stdio.h>
#include <unistd.h>
/*filename == mv   执行的目录？？？？*/
int main(void)
{
  printf("程序开始执行\n");
  char * args[4] = {"mv","test","/home/yh/unix c/test1",NULL};
  execvp("mv",args);
  printf("程序结束\n");
}
