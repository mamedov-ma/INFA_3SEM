#include     <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include <sys/types.h>
#include   <sys/ipc.h>
#include   <sys/msg.h>
#include    <unistd.h>
#include  <sys/time.h>

#define MSGSZ 128

typedef struct msgbuf{
    long    mtype;               // message type, must be > 0 
    char    mtext[MSGSZ];        // message text 
}msgbuf;

typedef struct detail{
    int gaika;  //max 2
    int vint;   //max 2
}detail;


void child(int qid, int k, msgbuf tmp, detail arr[], msgbuf msgs[])
{
    while(1)
    {
        if(msgrcv(qid, &tmp, MSGSZ, 1, IPC_NOWAIT) > 0)
        {
            k++;
            arr[k].gaika++;
            msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT);
        }
        if(msgrcv(qid, &tmp, MSGSZ, 3, IPC_NOWAIT) > 0)
        {
            if(arr[k].gaika == 0)
            {
                arr[k].gaika++;
                msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT);
            }
            else if(arr[k].gaika == 1)
            {
                arr[k].gaika++;
                msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT);
                msgsnd(qid, &msgs[0], strlen(msgs[0].mtext), IPC_NOWAIT);
                k++;
                arr[k].gaika++;
                msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT);
            }
        }
        if(msgrcv(qid, &tmp, MSGSZ, 2, IPC_NOWAIT) > 0)
        {
            if(arr[k].gaika == 0 || arr[k].vint == 0)
            {
                arr[k].gaika++;
                msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT);
            }
            else
            {
                arr[k].gaika++;
                msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT);
                msgsnd(qid, &msgs[0], strlen(msgs[0].mtext), IPC_NOWAIT);
                k++;
                arr[k].gaika++;
                msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT);
            }
        }
    
    }

};


void parent(int qid, int k, msgbuf tmp, detail arr[3], msgbuf msgs[3])
{
    while(1)
    {        
        if(msgrcv(qid, &tmp, MSGSZ, 1, IPC_NOWAIT) > 0)
        {
            k++;
            arr[k].vint++;
            if(msgsnd(qid, &msgs[2], strlen(msgs[2].mtext), IPC_NOWAIT) < 0){
                perror("sending error");
                exit(1);}
            else
                write(1, &msgs[2], strlen(msgs[2].mtext));
        }
        if(msgrcv(qid, &tmp, MSGSZ, 2, IPC_NOWAIT) > 0 && arr[k].vint == 1)
            arr[k].gaika++;
        if(msgrcv(qid, &tmp, MSGSZ, 2, IPC_NOWAIT) > 0 && arr[k].vint == 0)
        {
            arr[k].vint++;
            if(arr[k].gaika == 0)
                arr[k].gaika++;
            else if(arr[k].gaika == 1)
            {
                arr[k].vint++;
                if(msgsnd(qid, &msgs[0], strlen(msgs[0].mtext), IPC_NOWAIT) < 0){
                    perror("sending error");
                    exit(1);}
                else
                    write(1, &msgs[0], strlen(msgs[0].mtext));
                k++;
                arr[k].vint++;
                if(msgsnd(qid, &msgs[2], strlen(msgs[2].mtext), IPC_NOWAIT) < 0){
                    perror("sending error");
                    exit(1);}
                else 
                    write(1, &msgs[2], strlen(msgs[2].mtext));
            }
        }
    
    }
};  
    
    

int main(int argc, char * argv[])
{
    if(argc != 2){
        perror("one number is required!");
        return 0;}
    int k = 0,
        qid = msgget(IPC_PRIVATE, 0644),
        N = atoi(argv[1]);
    pid_t Pid;
    detail arr[N];
    msgbuf msgs[3], tmp;
    char* msg_text[3] = {"new detail","gaika installed","vint installed"};
    
    for(int i = 0; i < N; i++)
    {
        arr[i].gaika = 0;
	arr[i].vint = 0; 	
    }  
    
    for(int i = 0; i < 3; i++)
    {
        msgs[i].mtype = i + 1;
	strcpy(msgs[i].mtext, msg_text[i]); 	
    }    
     
    for(int i = 0; i < 2; i++)
    {
        if(Pid > 0)
            Pid = fork();
        if(Pid == 0)
            child(qid, k, tmp, arr, msgs);
    }
    
    parent(qid, k, tmp, arr, msgs);
    return 0;
}

