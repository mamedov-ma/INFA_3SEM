#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>


int main(int argc, char *argv[])
{
    int i = 0;
    struct passwd * info;
    struct group * group;
    char *name;    
    int _uid = (int) getuid();
    int _gid = (int) getgid();
    __gid_t *c = calloc(100, sizeof(int));
    int *a; 


    if(argc == 1)
    {
        info = getpwuid(_uid);

        name = info->pw_name;
  
        printf("uid=%d(%s) gid=%d(%s) groups=%d(%s)", _uid, name, _gid, name, _uid, name);   

        getgroups(100, c);

    }
    else
    {
        name = argv[1];

        info = getpwnam(name);

        if(getpwnam(name) == NULL)
	{
	    printf("id: ‘%s’: no such user\n", name);
	    return 0;
	}

        _uid = info->pw_uid;

	_gid = info->pw_gid;
         
        printf("uid=%d(%s) gid=%d(%s) groups=%d(%s)", _uid, name, _gid, name, _uid, name);
        
	*a = 100;
        	
        getgrouplist(name, _gid, c, a);         
	
    }

    while (c[i] != 0 && c[i] != _uid)
    {
         group = getgrgid(c[i]);

         name =  group->gr_name;

         printf(",%d(%s)", c[i], name);

         i++;
    }

    printf("\n");
    free(c);
    return 0;
}

