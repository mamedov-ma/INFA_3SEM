#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int fd[2];
    pipe(fd);
    pid_t f = fork();
    if (f != 0)
    {
        char str[4096], name[100];
        int j = 0, i = 0;
        ssize_t len;
        len = read(fd[0], str, 4096);
        write(1, str, len);
        close(fd[0]);
        close(fd[1]);
        while(str[j] != '\0')
        {
            if (str[j] != '\n')
            {
                name[i] = str[j];
                i += 1;
                j += 1;
            }
            else
            {
                printf("Name : \"%s\" \nCONTENT: \n", name);
                void *buff = malloc(1000);
                FILE *f1 = fopen(name, "r");
                while (fgets(buff, 1000, f1) != NULL)
                {
                    printf("%s", (char*)buff);
                }
                putchar('\n');
                for(int k = 0; k < 100; k ++)
                {
                    putchar('_');
                }
                putchar('\n');
                free(buff);
                for (int k = 0; k < 100; k ++)
                {
                    name[k] = '\0';
                }
                j += 1;
                i = 0;
            }
        }
    }
    else
    {
        close(fd[0]);
        dup2(fd[1], 1);
        execlp("ls", "ls", NULL);
        close(fd[1]);
    }
    return 0;
}
