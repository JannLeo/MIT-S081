// primers.c
// Author : Junnan Liu
// date: 05/04/2024
// update : 11/04/2024
// update : 12/04/2024

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//二维矩阵表示每个进程的管道
int p[34][2];
// void DFS(int pipe_num){
//     int flag = 0;
//     int i;
//     pipe_num %= 34;
//     if (pipe(p[pipe_num]) < 0) {
//         fprintf(2, "Error creating pipe\n");
//         exit(1);
//     }
//     int pid = fork();
//     while(read(p[pipe_num][0],&i,sizeof(int))){
//         if(i % num != 0 ){
//             if(!flag && pid == 0){
//                 fprintf(1,"%d\n",i);
//                 num = i;
//                 pipe_num += 1;
//                 flag = 1;
//                 pid = fork();
//             }
//             else if (pid < 0){
//                 fprintf(2, "Error forking\n");
//                 exit(2);
//             }
//             else{
//                 fprintf(1, "main write successfully %d DFS\n",i-2);
//                 write(p[pipe_num+1][1],&i,sizeof(int));
//             }
//         }
//     }
//     wait(0);
//     close(p[pipe_num][0]);
//     close(p[pipe_num][1]);
//     exit(0);
    
// }

int
main(int argc, char *argv[])
{
    int num=2;
    int flag=1;
    fprintf(1,"%d\n",num);
    if (pipe(p[0]) < 0) {
        fprintf(2, "Error creating pipe\n");
        exit(2);
    }
    int pid = fork();
    for(int i=num+1;i<=35;i++){
        if(i%num!= 0 ){
            if(pid==0 && flag){
                fprintf(1, "fork enter first time\n");
                int flagg = 0;
                int i;
                int pipe_num = 0;
                pipe_num %= 34;
                if (pipe(p[pipe_num]) < 0) {
                    fprintf(2, "Error creating pipe\n");
                    exit(1);
                }
                int pid = fork();
                fprintf(1, "Began to read\n");
                while(read(p[pipe_num][0],&i,sizeof(int))){
                    fprintf(1,"read number %d\n",i);
                    if(i % num != 0 ){
                        if(!flagg && pid == 0){
                            fprintf(1,"%d\n",i);
                            num = i;
                            pipe_num += 1;
                            flagg = 1;
                            pid = fork();
                        }
                        else if (pid < 0){
                            fprintf(2, "Error forking\n");
                            exit(2);
                        }
                        else{
                            fprintf(1, "main write successfully %d DFS\n",i-2);
                            write(p[pipe_num+1][1],&i,sizeof(int));
                        }
                    }
                }
                fprintf(1,"%d begin to wait\n",num);
                wait(0);
                close(p[pipe_num][0]);
                close(p[pipe_num][1]);
                exit(0);
                flag = 0;
            }
            else if(pid != 0){
                // fprintf(1, "Write number %d\n",i);
                write(p[0][1],&i,sizeof(int));
                // fprintf(1, "main write successfully %d\n",i-2);
            }
        }
    }
    wait(0);
    close(p[0][0]);
    close(p[0][1]);
    exit(0);
}
