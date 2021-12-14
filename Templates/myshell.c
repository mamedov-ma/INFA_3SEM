#include     <stdio.h>
#include <sys/types.h>
#include    <unistd.h>
#include  <sys/wait.h>
#include    <stdlib.h>
#include  <sys/time.h>
#include    <malloc.h>
#include    <string.h>
#define    _GNU_SOURSE




int main()
{
    char line[1000];
    char args[100][100];
    int k, p = 0;
    //pid_t Pid;
    while(1)
    {	    
	fprintf(stdout, "\n--------$");	
	fgets(line, 1000, stdin);
        int len = strlen(line);
        
        for(int i = 0; i < len; i++)
	{
	    if(line[i] == '|' || line[i + 1] == '\0')
	    {
		if(k == 0)
	            strncpy(args[k], &line[p], i - p);		
		else
		    strncpy(args[k], &line[p + 1], i - p - 1);
	        p = i;
		k++;
	    }
	}	
        fprintf(stdout, "%d\n", k);

	for(int i = 0; i < k; i++)
            write(1, args[i], 100); 
    

        
  	/*
	
	
	
	
	for(int i = 0; i < k; i++)
	{
	    if(Pid > 0)
            {
                pipe(fd[i][]);
	        Pid = fork();
		close(fd[i][0]);
		close(fd[i][1]);
            }
            else if(Pid == 0)
            {
	        if(i > 0)
		{
		    close(0);    
	            dup(fd[i - 1][0]);
		}
                if(i < k - 1)
		{
		    close(1);
		    dup(fd[i][1]);
		}
                
		
		close(fd[i][0]);
		close(fd[i][1]);

		p = i;
	    }
	    if (Pid < 0)
            {
                perror("fork");
                exit(1);
            }
	}

        if(Pid == 0)
	{
	    execvp();
	}*/
    }

    



    /*pid_t Pid = fork();

   

    size_t Size, len = 0;

    if (Pid < 0)
    {
        perr
    return 0;*/
 }
