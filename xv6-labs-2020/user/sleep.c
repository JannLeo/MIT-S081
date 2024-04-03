//sleep.c
// author : Junnan Liu
// date: 03/04/2024

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  //if without argument, the sleep will print an error message
  if(argc != 2){
    fprintf(2, "Error! The system call of sleep needs an argument.\n");
    exit(1);
  }
  int sleep_time = atoi(argv[1]);
  sleep(sleep_time);
  exit(0);
}
