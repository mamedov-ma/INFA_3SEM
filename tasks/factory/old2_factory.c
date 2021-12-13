#include     <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include <sys/types.h>
#include   <sys/ipc.h>
#include   <sys/msg.h>
#include    <unistd.h>
#include  <sys/time.h>

#define MSGSZ 128

#define ERR_CHECK( statement ) \
  if (statement)               \
  {                            \
    perror(#statement);        \
    _exit(1);                  \
  }                            \


typedef struct msgbuf{
    long    mtype;               // message type, must be > 0 
    char    mtext[20];        // message text 
}msgbuf;

typedef struct detail{
    int gaika;  //max 2
    int vint;   //max 2
}detail;


void child(int num, int N, int qid, int k, msgbuf tmp, detail arr[N], msgbuf msgs[8])
{  
    while(1)
    {             
        if(k > N)
            exit(1);
            
        if(msgrcv(qid, &tmp, MSGSZ, num*3 + 1, IPC_NOWAIT) > 0)
        {

            k++;
            arr[k].gaika++;
            ERR_CHECK(msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT) < 0);
            ERR_CHECK(msgsnd(qid, &msgs[4 + 3*(2 - num)], strlen(msgs[4 + 3*(2 - num)].mtext), IPC_NOWAIT) < 0);
            write(1, &msgs[num].mtext, strlen(msgs[num].mtext));

        }
        if(msgrcv(qid, &tmp, MSGSZ, num*3 + 3, IPC_NOWAIT) > 0)
        {
            arr[k].vint++;
            if(arr[k].gaika == 0)
            {
                arr[k].gaika++;
                ERR_CHECK(msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT) < 0);
                ERR_CHECK(msgsnd(qid, &msgs[4 + 3*(2 - num)], strlen(msgs[4 + 3*(2 - num)].mtext), IPC_NOWAIT) < 0);               
                write(1, &msgs[1].mtext, strlen(msgs[1].mtext));
            }
            else if(arr[k].gaika == 1)
            {
                arr[k].gaika++;
                ERR_CHECK(msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT) < 0);
                ERR_CHECK(msgsnd(qid, &msgs[4 + 3*(2 - num)], strlen(msgs[4 + 3*(2 - num)].mtext), IPC_NOWAIT) < 0);
                write(1, &msgs[1].mtext, strlen(msgs[1].mtext));
                k++;
                ERR_CHECK(msgsnd(qid, &msgs[0], strlen(msgs[0].mtext), IPC_NOWAIT) < 0);
                ERR_CHECK(msgsnd(qid, &msgs[3 + 3*(2 - num)], strlen(msgs[3 + 3*(2 - num)].mtext), IPC_NOWAIT) < 0);
                write(1, &msgs[0].mtext, strlen(msgs[0].mtext));
            }

        }
        if(msgrcv(qid, &tmp, MSGSZ, num*3 + 2, IPC_NOWAIT) > 0)
        {
            arr[k].gaika++;
            if(arr[k].gaika == 1)
            {
                arr[k].gaika++;
                ERR_CHECK(msgsnd(qid, &msgs[1], strlen(msgs[1].mtext), IPC_NOWAIT) < 0);
                ERR_CHECK(msgsnd(qid, &msgs[4 + 3*(2 - num)], strlen(msgs[4 + 3*(2 - num)].mtext), IPC_NOWAIT) < 0);
                write(1, &msgs[1].mtext, strlen(msgs[1].mtext)); 
                k++;
                ERR_CHECK(msgsnd(qid, &msgs[0], strlen(msgs[0].mtext), IPC_NOWAIT) < 0);
                ERR_CHECK(msgsnd(qid, &msgs[3 + 3*(2 - num)], strlen(msgs[3 + 3*(2 - num)].mtext), IPC_NOWAIT) < 0);
                write(1, &msgs[0].mtext, strlen(msgs[0].mtext));   
            }
        }  
    }
};


void parent(int N, int qid, int k, msgbuf tmp, detail arr[N], msgbuf msgs[8])
{  
    while(1)
    {        
        if(k == 0)
        {

            k++;
            ERR_CHECK(msgsnd(qid, &msgs[3], strlen(msgs[3].mtext), IPC_NOWAIT) < 0);
            ERR_CHECK(msgsnd(qid, &msgs[6], strlen(msgs[6].mtext), IPC_NOWAIT) < 0);
            write(1, &msgs[0].mtext, strlen(msgs[0].mtext)); 
            //usleep (1000000);
        }
        
        if(k > N)
            exit(1);
        
        if(msgrcv(qid, &tmp, MSGSZ, 1, IPC_NOWAIT) > 0)
        {

            k++;
            arr[k].vint++;
            ERR_CHECK(msgsnd(qid, &msgs[5], strlen(msgs[5].mtext), IPC_NOWAIT) < 0);
            ERR_CHECK(msgsnd(qid, &msgs[8], strlen(msgs[8].mtext), IPC_NOWAIT) < 0);
            write(1, &msgs[5].mtext, strlen(msgs[5].mtext));
            //usleep (1000000);

        }
        if(msgrcv(qid, &tmp, MSGSZ, 2, IPC_NOWAIT) > 0)
        {

            arr[k].gaika++;
            if(arr[k].vint == 0)
            {
                arr[k].vint++;
                ERR_CHECK(msgsnd(qid, &msgs[5], strlen(msgs[5].mtext), IPC_NOWAIT) < 0);
                ERR_CHECK(msgsnd(qid, &msgs[8], strlen(msgs[8].mtext), IPC_NOWAIT) < 0);
                write(1, &msgs[5].mtext, strlen(msgs[5].mtext));
            }
            if(arr[k].gaika == 2)
            {
                k++;
                ERR_CHECK(msgsnd(qid, &msgs[3], strlen(msgs[3].mtext), IPC_NOWAIT) < 0);
                ERR_CHECK(msgsnd(qid, &msgs[6], strlen(msgs[6].mtext), IPC_NOWAIT) < 0);
                write(1, &msgs[3].mtext, strlen(msgs[3].mtext));       
            }
            //usleep (1000000);  
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
    msgbuf msgs[8], tmp[3];
    char* msg_text[3] = {"new detail\n","gaika installed\n","vint installed\n"};
    
    for(int i = 0; i < N; i++)
    {
        arr[i].gaika = 0;
	arr[i].vint = 0; 	
    }  
    
    for(int i = 0; i < 3; i++)
    {
        msgs[i].mtype = i + 1;
	strcpy(msgs[i].mtext, msg_text[i]); 
	msgs[i + 3].mtype = i + 4;
	strcpy(msgs[i + 3].mtext, msg_text[i]); 
	msgs[i + 6].mtype = i + 7;
	strcpy(msgs[i + 6].mtext, msg_text[i]); 		
    }    
     
    for(int i = 1; i <= 2; i++)
    {
        if(Pid > 0)
            Pid = fork();
        if(Pid == 0)
            child(i, N, qid, k, tmp[i - 1], arr, msgs);
    }
    
    parent(N, qid, k, tmp[2], arr, msgs);
    
    return 0;
}

