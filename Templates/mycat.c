#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio_ext.h>


void mywrite(char *buf, size_t count);
void copy(char * pathname);


void mywrite(char *buf, size_t count)
{
   while(1)
   {
        size_t size = write(1, buf, count);
     
        switch(size)
        {
            case 0:
	    {  
		write(1, buf, 3);
                break;
	    }
            case -1:
            {
	        //perror(strerror(errno));
	        break;
	    }
        }
        
	if (size > 0 || size < count)
	{	
            buf += size;
            
	    count -= size;
	}
    }
}


void copy(char * pathname)
{
    char buf [1000]; 
       
    int fd = open(pathname, O_RDONLY);
    
    if(fd == -1)
    {
        //perror(strerror(errno));
        return;
    }

    while(1)
    {
        size_t size = read(fd, &buf, 1000);
        
	if(size == 0)
		break;

 	if(size < 0)
        {
            //perror(strerror(errno));
            break;
        }


	mywrite(&buf[0], size);
    }

    int end = close(fd);
    
    if(end == -1)
    {
        //perror(strerror(errno));
    }
}


int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            copy(argv[i]); 
        }
        
        //printf("%s", stdout);
        
    }    
    else if(argc == 1)
    {
	char buf[1000];    
       
        //fflush(stdout);  
	
	while(1)
	{
	    //scanf("%s", stdin);
		
	    size_t size = read(0, &buf[0], 1000);

            //fflush(stdin);
	    
	    //printf("%ld", size);

            if(size == 0)
                break;

            if(size < 0)
            {
                //perror(strerror(errno));
                break;
            }

            mywrite(&buf[0], size);
            //break;	    
	}    
    }
    
    return 0;                                                                                                         
}
