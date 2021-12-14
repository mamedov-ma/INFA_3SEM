#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>



int main(int argc, char *argv[])
{
    pid_t Pid;
    
    int a = 0;

    for(int i = 1; i < argc; i++)
    {
        if (Pid > 0)
        {
            Pid = fork();
            
	    a = i; 
	}
    }

    if (Pid == 0)
    {
        usleep(atoi(argv[a]) * 1000);

        printf("%d ", atoi(argv[a]));
    }	
  
    if(Pid > 0)
    {
        while(wait(NULL) > 0)		
	{}
        
	printf("\n");
    }

    return 0;
}

