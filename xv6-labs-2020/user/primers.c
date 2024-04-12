// primers.c
// Author : Junnan Liu
// date: 05/04/2024
// update : 11/04/2024
// update : 12/04/2024

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//二维矩阵表示每个进程的管道

void DFS(int fd){
    int i;
    int num;
    //读取第一个值
    read (fd,num,sizeof(int));
    fprintf(1, "%d \n",num);
    //创建管道
    int p[2];
    if (pipe(p) < 0) {
        fprintf(2, "Error creating pipe\n");
        exit(1);
    }
    int temp = -1;
    while(1){
        temp = read(fd,&i,sizeof(int));
        if(temp < 0)
            break;
        if(i % num != 0 ){
            fprintf(1, "Write successfully %d DFS\n",i-2);
            write(p[1],&i,sizeof(int));
        }
    }
    if(temp==-1){
        close(p[1]);
        close(p[0]);
        close(fd);
        return;
    }
    int pid = fork();
    if(pid == 0){
        close(p[1]);
        close(fd);
        DFS(p[0]);
        close(p[0]);
    }else{
        close(p[1]);
        close(p[0]);
        close(fd);
        wait(0);
    }
}

int
main(int argc, char *argv[])
{
    int flag=1;
    int p[2];
    if (pipe(p) < 0) {
        fprintf(2, "Error creating pipe\n");
        exit(2);
    }
    int pipe_num = 1;
    for(int i=2;i<=35;i++){
        int num;
        write(p[1],&num,sizeof(int));
    }
    close(p[1]);
    DFS(p[0]);
    close(p[0]);
    
    exit(1);
}
