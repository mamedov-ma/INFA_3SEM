#include     <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include <sys/types.h>
#include   <sys/ipc.h>
#include   <sys/msg.h>
#include    <unistd.h>
#include  <sys/time.h>

#define MSGSZ 128


//open forks at the same time

//all childs are ready

//open message queue

//parent makes a start and starts counting time 

//each child has it's own number and message key

//when some child receive a message, he send a message to the next child or parent(if he was last), then make a "return"

//parent receive a message, stop counting, print a runtime, then close message queue 




typedef struct msgbuf{
    long    mtype;               // message type, must be > 0 
    char    mtext[MSGSZ];        // message text 
}msgbuf;




int main(int argc, char * argv[])
{
    pid_t Pid = 1;
    int N = atoi(argv[1]);
    msgbuf arr[N];		
    msgbuf arrsv[N];
    int k = 0;
    int qid = msgget(IPC_PRIVATE, 0644);
    struct timeval t1, t2;

    for(int i = 0; i < N; i++)
    {
        arr[i].mtype = i + 1;
	strcpy(arr[i].mtext, "lap"); 
        
        //printf("%ld %s", arr[i].mtype, arr[i].mtext);	
    }
    //printf("%d", qid);
    
    for(int i = 0; i < N; i++)
    {
    // Initialise all childs, make them a number

        if(Pid > 0)
        {
            k = i;
	    Pid = fork();               
        }
        else if(Pid == 0)
        {
	    //usleep(1000000);
	    //printf("%d", k);
	    break;
        }
        if (Pid < 0)
        {
            perror("fork");
            exit(1);
        }
    }
    
   
    if (Pid > 0)
        gettimeofday(&t1, NULL);

    
    while(1)
    {
        if(Pid == 0)
        {
            if(k == 0)
	    {
	        if(msgsnd(qid, &arr[k], strlen(arr[k].mtext), IPC_NOWAIT) < 0)
		{
		    printf("%d %d, %ld, %s, %ld\n", msgsnd(qid, &arr[k], strlen(arr[k].mtext), IPC_NOWAIT), qid, arr[k].mtype, arr[k].mtext, strlen(arr[k].mtext));
		    perror("msgsnd");
		    break;
	        }
	        else
		    printf("%dth %s\n", k + 1, arr[k].mtext);
		break;
	    }		    
            else    
	    {
                if(msgrcv(qid, &arrsv[k - 1], MSGSZ, k, IPC_NOWAIT) < 0)
		{
		    //perror("msgrcv");
                    //exit(1);
		}
		else
                {
                    if(msgsnd(qid, &arr[k], strlen(arr[k].mtext), IPC_NOWAIT) < 0)
                    {
                        printf("%d, %ld, %s, %ld\n", qid, arr[k].mtype, arr[k].mtext, strlen(arr[k].mtext));
                        perror("msgsnd");
                        break;
		    }
                    else
                        printf("%dth %s\n", k + 1, arr[k].mtext);
                    break;
                }
		
 	    }
        }
        
        if(Pid > 0)
        {
	    if(msgrcv(qid, &arrsv[k], MSGSZ, k + 1, IPC_NOWAIT) < 0)
            {
	        //perror("msgrcv");
		//exit(1);
	    }
            else
            {
                gettimeofday(&t2, NULL);
                
                float time = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 0.000001;

	        printf("%.6lf\n", time);
	       
	        break;	
            }  
        }
    } 
    return 0;     
}
