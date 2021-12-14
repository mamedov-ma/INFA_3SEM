#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>




int main(int argc, char * argv[])
{   
    if(argc != 2)
    {
        printf("Wrong enter, you have to write down int number > 0 !!!");
	return 0;
    }
   
    int n = atoi(argv[1]);
    int len = strlen(argv[1]);

    for(int i = 0; i < len; i++)
    {       	   
        if(!isdigit(argv[1][i]))
	{
            printf("Wrong enter, you have to write down int number > 0 !!!");
            return 0;
        }	
    }
      
    if(n < 1)
    {
        printf("Wrong enter, you have to write down int number > 0 !!!");
        return 0;
    }
    
    //char buffer[10000];
    //setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));
 
    for(int i = 1; i <= n; i++)
	    printf("%d ", i);

    return 0;
}
