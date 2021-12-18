#include "33.h"


int main()
{
    const char* buf;
    char line[100];

    printf("Enter the string please: ");
    fgets(line, 100, stdin);

    strcpy(&line[strlen(line) - 1], "");
    buf = line;
    int Num = 33;
    int len = strlen(buf);

    for (int i = 0; i < Num; i++)
    {
        pid_t Pid = fork();
        if (Pid == 0)
        {
            child(i, buf, len);
            return 0;
        }
    }

    for (int i = 0; i < Num; i++)
    {
        ERR_CHECK(wait(NULL) < 0);
    }
    
    //cleaning
    key_t key = ftok("33.c", 0);
    int sem_id = semget(key, SEM_NUM, ACCESS);
    semctl(sem_id, 0, IPC_RMID);
    int shm_id = shmget(key, sizeof(alphabet), ACCESS);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}


void child(int Pid, const char* buf, int len)
{
    int i = 0;
    char c = 0;
      
    key_t key = ftok("33.c", 0);   
    int sem_id = semget(key, SEM_NUM, IPC_CREAT | IPC_EXCL | ACCESS);
       
    if ((sem_id == -1) && (errno == EEXIST))
    {
        sem_id = semget(key, SEM_NUM, ACCESS);      
    }
    else
    {
        V(sem_id, UNIQUE, 1);
    }

    int shm_id = shmget(key, sizeof(alphabet), IPC_CREAT | IPC_EXCL | ACCESS);
    if ((shm_id == -1) && (errno == EEXIST))
    {
        shm_id = shmget(key, sizeof(alphabet), ACCESS);
    }
    alphabet* taken = shmat(shm_id, NULL, 0);
   
    while (i < len)
    {
        P(sem_id, UNIQUE, 1);
        i = semctl(sem_id, Ind, GETVAL);
        if (i == len)
        {
            V(sem_id, UNIQUE, 1);
            break;
        }

        if ((c == 0) && letter_check(*taken, buf[i]))
        {
            c = buf[i];
            printf("proces %02d:  %c\n", Pid, c);

            taken->arr[taken->arr_size] = c;
            (taken->arr_size)++;

            V(sem_id, Ind, 1);
            i++;
        }
        else if (c == buf[i])
        {
            printf("proces %02d:  %c\n", Pid, c);
            V(sem_id, Ind, 1);
            i++;
        }

        V(sem_id, UNIQUE, 1);  
    }
  
    shmdt(taken);
}

int letter_check(alphabet taken, char letter) 
{
    int len = taken.arr_size;
    int status = 1;
    for (int i = 0; i < len; i++)
    {
        if (taken.arr[i] == letter)
        {
            status = 0;
            break;
        }
    }

    return status;
}

void P( int sem_id, SemInd ind, short delta )
{
  sembuf buf = {ind, -delta, 0};
  ERR_CHECK(semop(sem_id, &buf, 1) > 0);
}

void V( int sem_id, SemInd ind, short delta )
{
  sembuf buf = {ind, delta, 0};
  ERR_CHECK(semop(sem_id, &buf, 1) > 0);
}

void Z( int sem_id, SemInd ind )
{
  sembuf buf = {ind, 0, 0};
  ERR_CHECK(semop(sem_id, &buf, 1) > 0);
}

int Z_NO_WAIT( int sem_id, SemInd ind )
{
  sembuf buf = {ind, 0, IPC_NOWAIT};
  return semop(sem_id, &buf, 1);
}


