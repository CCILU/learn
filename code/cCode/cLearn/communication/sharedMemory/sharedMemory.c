#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
int main() {
    int shmId = 0;
    char *myShm = NULL;
    int pid = 0;

    shmId = shmget(IPC_PRIVATE, 255, 0);
    if(0 > shmId) {
        printf("shmget error !\n");
        return -1;
    }
    system("ipcs -m");
    pid = fork();
    if(pid > 0) {
        myShm = (char*)shmat(shmId, NULL, 0777);
        if(0 > myShm) {
            printf("shmat error !\n");
            return -1;
        }
        printf("parent input :\n");
        fgets(myShm, 255, stdin);
        kill(pid,SIGUSR1);
        shmdt(myShm);
    }
    if(pid == 0) {
        myShm = (char*)shmat(shmId, NULL, 0777);
        if(0 > myShm) {
            printf("shmat error !\n");
            return -1;
        }
        pause();
        printf("son out put:\n");
        printf("%s", myShm);
        shmdt(myShm);
    }

    shmctl(shmId, IPC_RMID, NULL);
    system("ipcs -m");
    return 0;
}