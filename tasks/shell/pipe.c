#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

int count_pipe(char* s) {
    int count = 0;
    int len = strlen(s);
    for(int i = 0; i < len; i++) {
        if ( s[i] == '|' ) {
            count++;
        }
    }
    return count;
}

void closed(int* arr, int count) {
    int i = 0;
    while(i < count) { // There are while, so we need close every fork()
        close(arr[2 * i]);
        close(arr[2 * i + 1]);
        i++;
    }
}

void execute(char* command, int* arr, int count, int num) {
    int len = strlen(command);
    char **action = (char**)malloc(len);
    int i = 0;
    while( (action[i] = strtok_r(command, " ", &command)) ) {
        i += 1;
    }
    if (num != 0) {
        dup2(arr[2 * (num - 1)], 0);
    }
    if (num < (count - 1)) {
        dup2(arr[2 * num + 1], 1);
    }
    closed(arr, count);
    int check = execvp(action[0], action);
    if ( check < 0 ) {
        fprintf(stderr, "ERROR IN COMMAND\n");
        exit(6);
    }
}

void check(char* buf) {
        int len = strlen(buf);
        char **action = (char**)malloc(len);
        int i = 0;
        while( (action[i] = strtok_r(buf, " ", &buf)) ) {
            i += 1;
            printf("%s", action[i]);
        }
        //printf("%s", action[0]);
        pid_t Pid = fork();
        if (Pid == 0)
            execvp(action[0], action);
}



int main(int argc, char* argv[]) 
{
    char* buf = (char*)calloc(1000, sizeof(char));    
    char* buf2 = (char*)calloc(1000, sizeof(char));
    
    while(1)
    {
        next:
        fprintf(stdout, "\n--------$");	
        fgets(buf2, 1000, stdin);
        int size = strlen(buf2) - 1;
        strncpy(buf, buf2, strlen(buf2) - 1);
        int count = count_pipe(buf);
        
        //fprintf(stdout, "%d", count);
        
        if ( count == 0 ) { 
            check(buf); 
            goto next;     
        }
        count++;
        
        int pipe_arr[count * 2];
        for(int i = 0; i < count; i++) {
            pipe((int*)pipe_arr + i * 2);
        }
        char **command = (char**)malloc(size);
        strcpy(buf2, buf);
        for(int i = 0; i < count; i++) {
            
            command[i] = strtok_r(buf2, "|", &buf2);
            //printf("\n'%s'\n", command);
           
            pid_t kid = fork();
            if ( kid == 0 ) {
                execute(command[i], (int*) pipe_arr, count, i);
            }
        }
        closed((int*) pipe_arr, count); // close last fork()
        for(int i = 0; i < count + 1; ++i) {
            wait(NULL);
        }
     
    }
    return 0;
}
