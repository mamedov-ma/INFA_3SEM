#include     <stdio.h>
#include <sys/types.h>
#include    <unistd.h>
#include  <sys/wait.h>
#include    <stdlib.h>
#include  <sys/time.h>
#include    <malloc.h>

#define READ  fd[0]
#define WRITE fd[1]



int main(int argc, char *argv[])
{
    int fd[2];

    pipe(fd);

    int opt = getopt(argc, argv, "-f");

    if (opt != 1 && opt != 102)
	    return 0;

    pid_t Pid = fork();

    struct timeval t1, t2;

    size_t Size, len = 0;

    if (Pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (Pid == 0)
    {
        close(1);
	dup(WRITE);	    
	
	close(READ);
	close(WRITE);
	   
	if(opt == 1)
	    execvp(argv[1], argv + 1);
	else if(opt == 102)
            execvp(argv[2], argv + 2);

	perror("WTF");
    }
    else
    {	
	gettimeofday(&t1, NULL);
	
        char *buf = (char*)calloc(1000, sizeof(char));

	while(1)
	{	
	    Size = read(READ, buf, 1000);
	    
	    len = len + Size;
	    
	    if(opt == 1)
	        write(1, buf, Size);
	   
	    if(Size < 999)
                break;
	}
	
        close(WRITE);

	close(READ);
	
	wait(NULL);
       
     	gettimeofday(&t2, NULL);
        
        float time = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 0.000001;
	
	fprintf(stderr,"%.6lf, %ld, %d\n",time, len, opt);

	free(buf);
    }
    
    return 0;
}
