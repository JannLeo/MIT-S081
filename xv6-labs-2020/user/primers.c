// primers.c
// Author : Junnan Liu
// date: 05/04/2024

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p[34][2];
    int num=2;
    int flag=0;
    fprintf(1,"%d\n",num);
    //主进程
    for(int i=num+1;i<=35;i++){
        if(i==flag && pipe(p[i-3])<0){
            fprintf(2,"error for pipe\n");
            exit(1);
        }
        //子进程 但是只能等到主进程产生之后才能read
        if(i==flag && fork()==0){
            int n;
            int flagg=0;
            while(read(p[i-3][0],&n,sizeof(int))){
                if(!flagg){
                    num=n;
                    fprintf(1,"%d\n",n);
                    flagg=num;
                    flag = num;
                }
                if(num<n && n%num!=0){
                    write(p[num-3][1],&n,sizeof(int));
                }
                
            }
            if(!flagg){
                close(p[i-3][1]);
            }
            close(p[i-3][0]);
        }
        //主进程
        else{
            if(i%num!=0){
                write(p[i-3][1],&i,sizeof(int));
                if(!flag){
                    flag=i;
                }
            }
        }
        
    }
    close(p[0][0]);
    close(p[0][1]);
    
    exit(0);
}
