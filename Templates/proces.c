#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    int st = atoi(argv[1]);
    
    pid_t Pid = fork();
    
   // printf("parent %d %d\n", getppid(), getpid());

    
    for(int i = 0; i < st; i++)
    {     
        if (Pid < 0)
        {
	    perror("fork");
	    exit(1);
	}
	else if (Pid == 0)
	{
	    printf("child %d %d\n", getppid(), getpid());

	    Pid = fork();
             
	}
	else
	{
       	    //printf("parent %d %d\n", getppid(), getpid());
	    wait(NULL);
	    return 0;
	}
    }
    
    return 0;
}
