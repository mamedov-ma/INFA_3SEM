#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    FILE* fp;
    char str[1024];
    if (argc != 3)
    {
        printf("3 arguments needed\n");
        return 0;
    }
    int fd[2];
    pipe(fd);
    pid_t f = fork();
    if (f != 0)
    {
        close(fd[0]);
        if ((fp = fopen(argv[1], "r")) == NULL)
        {
            printf("Cannot open file to read\n");
            return 0;
        }
        while (!feof(fp))
        {
            if (fgets(str, 1024, fp))
            {
                write(fd[1], str, 1024);
            }
        }
        fclose(fp);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        if ((fp = fopen(argv[2], "w")) == NULL)
        {
            printf("Cannot open file to write\n");
            return 0;
        }
        while (read(fd[0], str, 1024))
        {
            fputs(str, fp);
        }
        fclose(fp);
        close(fd[0]);
    }
    return 0;
}
