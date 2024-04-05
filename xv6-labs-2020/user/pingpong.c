// pingpong.c
// author : Junnan Liu
// date: 05/04/2024

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  char str[1024];
  if(pipe(p)<0){
    fprintf(2,"error for pipe\n");
    exit(1);
  }
  int pro_num = getpid();
  if(fork() == 0){
    read(p[0],str,4);
    close(p[0]);
    write(p[1],"pong",4);
    close(p[1]);
    fprintf(1,"%d : received %s\n",pro_num,str);
  }
  else{
    read(p[0],str,4);
    close(p[0]);
    write(p[1],"ping",4);
    close(p[1]);
    fprintf(1,"%d : received %s\n",pro_num,str);
    wait(0);
  }
  exit(0);
}
