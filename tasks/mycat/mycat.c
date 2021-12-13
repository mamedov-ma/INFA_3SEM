#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <sys/poll.h>


void mywrite(int Out, char * buf, int count)
{
    size_t size = write(Out, buf, count);
    char* p = buf + size;    
    if (size < count)
    {            
        while(1)
        {	
            size = write(Out, buf, 1);
            buf += size;
	    count -= size;
	    if(count == 0)
	        break;
        }
    }
}


void child(int In, int Out)
{
    char* buf = (char*)calloc(1000, sizeof(char));

    while(1)
    {
        int count = read(In, buf, 1000);
        size_t size = write(Out, buf, count);
	char* p = buf + size;    
        mywrite(Out, buf, count);
    }
}


void parent(int k, int(*)fd, struct pollfd fd_arr)
{
    char buf[k][1000];
    
    while(1)
    {
        for(int i = 0; i < k; i++)
        {
            if(strlen(buf[i]) > 0)
            {
                fd_arr[i].fd = fd[i][1];
                fd_arr[i].events = POLLOUT;
                fd_arr[k + i].fd = NULL;
                fd_arr[k + i].events = NULL;  
            }
            else
            {
                fd_arr[i].fd = NULL;
                fd_arr[i].events = NULL;
                fd_arr[k + i].fd = fd[k + i][0];
                fd_arr[k + i].events = POLLIN;  
            }
        }
        poll(fd_arr, 2 * k, 100);
       
        for(int i = 0; i < k; i++)
        {
            if(fd_arr[i].revents > 0 == POLLOUT)
            {
                write(fd_arr[i].fd, &buf[i][0], strlen(buf[i]);
                memset(buf[i], 0, sizeof(buf[i]));
                
            }
            if(fd_arr[100 - i].revents > 0 == POLLIN)
            {
                read(fd_arr[100 - i].fd, &buf[i + 1][0], 1000);
            }
        }
    }       
}


int main(int argc, char**argv)
{
    pid_t Pid;
    int k = atoi(argv[2]);
    int fd[k * 2][2];
    int p = 0;
    struct pollfd fd_arr[k];

    for(int i = 0; i < k; i++)
    {
	if(Pid > 0)
            pipe(fd[i]);
	    pipe(fd[k + i]);                 
            p = i;
            Pid = fork();
        }
        if(Pid == 0){
            child(fd[p][0], fd[k + p][1]);
	}
	if (Pid < 0){
            perror("fork");
            exit(1);
	}

        for(int i = 0; i < k; i++)
        {
            fd_arr[i].fd = fd[i][1];
            fd_arr[i].events = POLLOUT;
          
            fd_arr[k + i].fd = fd[k + i][0];
            fd_arr[k + i].events = POLLIN;        
        }
        parent(k, fd, fd_arr);
}
