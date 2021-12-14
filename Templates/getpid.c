#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

       
      

int main()
{
    int a = (int) getpid();    
 
    int b = (int) getppid();
   
    printf("%d ", a);
    
    printf("%d", b);
    
    return 0;
}
