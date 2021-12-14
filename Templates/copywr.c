#include <stdlib.h>
#include <stdio.h>

int main(int argc ,char *argv[])
{
     FILE * s1, *s2;
     char * str;

     s1 = fopen(argv[1], "r");
     s2 = fopen(argv[2], "w");
     
     if  (s1 == NULL || s2 == NULL)
     {
         printf("Can't open file (((");
         getchar();
         return 0;
     }

     fscanf(s1, "%s", str);
     
     fclose(s1);

     fprintf(s2, "%s", str);
     
     fclose(s2); 
    
     return 0;
}


