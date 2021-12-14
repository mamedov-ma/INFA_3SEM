#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

typedef struct LS{
    char opt[10];
    char dir[PATH_MAX];
}LS;


void myls(LS param)
{
    /*DIR *dir; 
    struct stat  *buf;
    int i;

    dir = opendir(param.dir);
   
    if (!dir) 
    {
        perror("diropen");
        exit(1);
    }

    while ( (i = lstat(param.dir, buf)) != -1) 
    {
        //printf("%ld - %s [%d] %d\n",
           // entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
	printf("%ld\n", buf->st_dev);
    };

    closedir(dir);*/

    printf("%s %s\n", param.opt, param.dir);
}



int main(int argc, char* argv[])
{
   LS *arg_lst = (LS*)calloc(argc, sizeof(LS));
       
   char **buf;
   
   buf[0] = (char*)calloc(200, sizeof(char));
   buf[1] = (char*)calloc(200, sizeof(char));
   
   char * PN = getcwd(buf[1], PATH_MAX);
   
   int i = 0;
   int k = 0;

   char *opts = "-l-a-t-i-n-R";
  
   printf("%d", getopt(argc, argv, opts));
 
   while(1)
   {
       if(argc == 1)
       {
           strcpy(arg_lst[i].dir,buf[1]);
	   break;	   
       }
       
       strcpy(buf[0], argv[i + 1]); 	   
       
       k = getopt(3, buf, opts);

       printf("%d", k);
       
       if(k != 1)
       {
           strcpy(arg_lst[i].opt, argv[i + 1]);	   
           
	   if(i < argc - 2)
	   {
	       strcpy(buf[0],argv[i + 2]);

	       k = getopt(3, buf, opts);

               printf("%d", k);
	   }
	   else break;    	   
        }
        else if(k == 1)
        {
            strcpy(arg_lst[i].dir, argv[i + 1]);
          
            if(i < argc - 2)
	    {
	        i++;
	        goto next;
	    }
	    else break; 
        }
        if(k != 1)
        {
	    strcpy(arg_lst[i].dir,buf[1]);
	    i++;
        }
        else if(k == 1)
        {
            i++;

	    strcpy(arg_lst[i].dir, argv[i + 1]);
           
	    if(i < argc - 2)
	    {
                i++;
	    }
	    else break;
        }
        
        
        next: i += 0;
    }

    for(int j = 0; j <= i; j++)
    {
        myls(arg_lst[j]);
    }

    return 0;
} 
