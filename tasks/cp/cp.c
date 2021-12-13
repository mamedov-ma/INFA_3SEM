#include <stdio.h>
#include <getopt.h>
#include <sys/stat.h>
#include <errno.h>
#include <utime.h>

void print_cp(char* path_from, char* path_to, int flag_v, int flag_i, int flag_f, int flag_p);




int main(int argc, char** argv)
{
    const struct option long_option[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'},
        {"interactive", no_argument, NULL, 'i'},
        {"force", no_argument, NULL, 'f'},
        {"preserve", no_argument, NULL, 'p'},
        {NULL, no_argument, NULL, 0}
    };
    
    int long_index;
    const char short_option[] = "hvifp";
    int opt;
    int flag_h = 0, flag_v = 0, flag_i = 0, flag_f = 0, flag_p = 0;
    
    while((opt = getopt_long(argc, argv, short_option, long_option, &long_index)) != -1)
    {
        switch(opt)
        {
        case 'h': flag_h = 1;
            break;
        case 'v': flag_v = 1;
            break;
        case 'i': flag_i = 1;
            break;
        case 'f': flag_f = 1;
            break;
        case 'p': flag_p = 1;
            break;
        case '?': printf("Неизвестный парамтер: -%c\n", optopt);
        }
    }
    
    if (flag_h == 1)
    {
        printf("\nNAME\n");
        printf("\tcp -- copy files\n");
        printf("\nSYNOPSIS\n");
        printf("\tcp [-h | -v | -i | -f | -p] source_file target_file\n");
        printf("\nDESCRIPTION\n");
        printf("\tFlags:\n\n");
        printf("\t -h\t help\n");
        printf("\t -v\t verbose\n");
        printf("\t -i\t interactive\n");
        printf("\t -f\t force\n");
        printf("\t -p\t preserve\n");
        printf("\n");
        return 0;
    }
    
    if (argc <= optind + 1)
    {
        printf("To few arguments\n");
        return 0;
    }
    
    print_cp(argv[optind], argv[optind + 1], flag_v, flag_i, flag_f, flag_p);
    
    return 0;
}



void print_cp(char* path_from, char* path_to, int flag_v, int flag_i, int flag_f, int flag_p)
{
    FILE* file_from = fopen(path_from, "r");
    
    if (file_from == NULL)
    {
        printf("Wrong 1 argument\n");
        return;
    }
    
    if (access(path_to, F_OK) != -1 && flag_i == 1)
    {
        printf("Overwrite %s? (y/n [n])\n", path_to);
        int answer = getc(stdin);
        if (answer != 'y')
        {
            printf("Not overwritten\n");
            fclose(file_from);
            return;
        }
    }
    
    FILE* file_to = fopen(path_to, "w");
    
    if (file_to == NULL && errno == EACCES && flag_f == 1)
    {
        remove(path_to);
        file_to = fopen(path_to, "w");
    }
    
    if (file_to == NULL)
    {
        printf("Wrong with 2 argument\n");
        fclose(file_from);
        return;
    }
    
    char symb;
    
    while (fread(&symb, 1, 1, file_from))
    {
        fwrite(&symb, 1, 1, file_to);
    }
    
    if (flag_v == 1)
    {
        printf("\"%s\" > \"%s\"\n", path_from, path_to);
    }
    
    if (flag_p == 1)
    {
        struct stat filestat;
        stat(path_from, &filestat);
        chmod(path_to, filestat.st_mode);
        chown(path_to, filestat.st_uid, filestat.st_gid);
        struct utimbuf Time;
        Time.actime = filestat.st_atimespec.tv_sec;
        Time.modtime = filestat.st_mtimespec.tv_sec;
        utime(path_to, &Time);
    }
    
    fclose(file_from);
    fclose(file_to);
}

