#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>



int main(int argc, char *argv[])
{
    pid_t Pid = fork();

    if (Pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (Pid == 0)
    {
        execvp(argv[1], argv + 1);
        perror("WTF");
    }
    else
    {
        struct timeval t1;

    	struct timeval t2;
	    
	gettimeofday(&t1, NULL);
	
	wait(NULL);
       
       	gettimeofday(&t2, NULL);
        
        float time = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 0.000001;

	printf("%.6lf\n", time);
      
    }
    
    return 0;
}
