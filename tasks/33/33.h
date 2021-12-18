#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/param.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_MEM_SIZE  4096
#define ACCESS        0777
#define SEM_NUM          2

#define ERR_CHECK( statement ) \
  if (statement)               \
  {                            \
    perror(#statement);        \
    _exit(1);                  \
  }                            \

typedef struct sembuf sembuf;

typedef enum SemInd
{
    UNIQUE = 0,         // Indicate that letter is brought up only by one process
    Ind,                // Indew of a current letter in buf
}SemInd;
char c = 0;
typedef struct alphabet
{
    int arr_size;
    char arr[33];
}alphabet;

void P( int sem_id, SemInd ind, short delta );
void V( int sem_id, SemInd ind, short delta );
void Z( int sem_id, SemInd ind );
int Z_NO_WAIT( int sem_id, SemInd ind );
int letter_check(alphabet taken, char letter);
void child(int Pid, const char* buf, int len);


