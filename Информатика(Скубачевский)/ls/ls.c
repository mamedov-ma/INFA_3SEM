#include <stdio.h>
#include <sys/stat.h>
#include <getopt.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>

void print_ls(char* path, int flag_a, int flag_R, int flag_l)
{
    DIR* my_dir;
    struct dirent* file;
    struct stat filestat;
    my_dir = opendir(path);
    while((file = readdir(my_dir)) != NULL)
    {
        if (flag_a == 0 && file->d_name[0] == '.') 
        {
            continue;
        }
        char new_path[512];
        snprintf(new_path, 512, "%s/%s", path, file->d_name);
        stat(new_path, &filestat);
        if (flag_l == 1)
        {
            struct passwd* owner = getpwuid(filestat.st_uid);
            struct group* group = getgrgid(filestat.st_gid);
            char time[50];
            printf("%-4hu", filestat.st_nlink);
            printf("%-20s", owner->pw_name);
            printf("%-8s", group->gr_name);
            printf("%-6lld", filestat.st_size);
            strftime(time, 50, "%e %b %H:%M", localtime(&filestat.st_mtime));
            printf(" %s", time);
            printf(" ");
        }
        printf("%s", file->d_name);
        if (S_ISDIR(filestat.st_mode) == 1)
        {
            printf("/");
        }
        printf("\n");
    }
    closedir(my_dir);
    if (flag_R == 0) 
    {
        return;
    }
    printf("\n");
    my_dir = opendir(path);
    while((file = readdir(my_dir)) != NULL)
    {
        if (flag_a == 0 && file->d_name[0] == '.')
        {
            continue;
        }
        char new_path[512];
        snprintf(new_path, 512, "%s/%s", path, file->d_name);
        stat(new_path, &filestat);
        if (S_ISDIR(filestat.st_mode) == 1)
        {
            char new_path[512];
            snprintf(new_path, 512, "%s/%s", path, file->d_name);
            printf("%s:\n", new_path);
            print_ls(new_path, flag_a, flag_R, flag_l);
        }
    }
    closedir(my_dir);
}

int main(int argc, char** argv)
{
    const struct option long_option[] =
    {
        {"all", no_argument, NULL, 'a'},
        {"recursive", no_argument, NULL, 'R'},
        {"long", no_argument, NULL, 'l'},
        {NULL, no_argument, NULL, 0}
    };
    int long_index;
    const char short_option[] = "aRl";
    int opt;
    int flag_a = 0, flag_R = 0, flag_l = 0;
    while((opt = getopt_long(argc, argv, short_option, long_option, &long_index)) != -1)
    {
        switch(opt)
        {
        case 'R': flag_R = 1;
            break;
        case 'a': flag_a = 1;
            break;
        case 'l': flag_l = 1;
            break;
        case '?': printf("Неизвестный парамтер: -%c\n", optopt);
        }
    }
    print_ls(argv[optind] == NULL ? "." : argv[optind], flag_a, flag_R, flag_l);
    return 0;
}
