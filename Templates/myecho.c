#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int bk = 1;
    char *end = "\n";
    
    if(argc == 1)
    {
       printf("\n");
       return 0;
    }
    
    if(strcmp(argv[1], "-n") == 0) 
    {
        bk = 2;
        end = "";
        argv[1] = "";
    }
      
    if(argc > 1)
    {
        for(int i = bk; i < argc - 1; i++)
            printf("%s ", argv[i]);
        printf("%s%s", argv[argc - 1], end);
        
    }
   
    return 0;
}
