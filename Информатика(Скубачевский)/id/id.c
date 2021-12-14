#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <string.h>
int main(int argc, char **argv)
{
    int flag_g, flag_u, flag_G;
    int opt;
    struct group* gr;
    char* name;
    name = getpwuid(getuid()) -> pw_name;
    while((opt = getopt(argc,argv, "ugG")) != -1)
    {
        switch(opt)
        {
        case 'g': flag_g = 1;
            break;
        case 'u': flag_u = 1;
            break;
        case 'G': flag_G = 1;
        }
    }
    if (flag_u == 1)
    {
        printf("%d ", getuid());
    }
    else if (flag_g == 1)
    {
        printf("%d ", getgid());
    }
    else if (flag_G == 1)
    {
        printf("%d ", getgid());
        while((gr = getgrent()) != NULL)
        {
            for(int i = 0; gr -> gr_mem[i] != NULL; i++)
            {
                if(strcmp(name, gr -> gr_mem[i]) == 0)
                    printf("%d ", gr -> gr_gid);
            }
        }
    }
    else
    {
        printf("uid=%d(%s) ", getuid(), getpwuid(getuid()) -> pw_name);
        printf("gid=%d(%s) ", getgid(), getgrgid(getgid()) -> gr_name);
        printf("groups=%d(%s),", getgid(), getgrgid(getgid()) -> gr_name);
        while((gr = getgrent()) != NULL)
        {
            for(int i = 0; gr -> gr_mem[i] != NULL; i++)
            {
                if(strcmp(name, gr -> gr_mem[i]) == 0)
                    printf("%d(%s),", gr -> gr_gid, gr -> gr_name); 
            }
        }
    }
}
