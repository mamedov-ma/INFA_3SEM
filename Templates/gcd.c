#include <stdio.h>
#include <stdlib.h>

int iabs(int x) { return (x < 0) ? -x : x; }

int eu_mod(int x, int y)
{
    int r = x % y;
    if (r < 0) r += iabs(y);
    return r;
}

int gcd(int x, int y)
{
    int q = eu_mod(x, y);
    if (q == 0) return y;
    return gcd(y, q);
}

int main(int argc, char	*argv[])
{
    if(argc > 3)
    {
        printf("Wrong enter: you have to write down two int numbers!!!");
	abort();
    }

    int x,y = 0;
    
    
    strtol(argv[1], &argv[2], x);
    strtol(argv[2], &argv[3], y);
    
    printf("%d %d", x, y);

    //gcd(*x, *y);

    return 0;
}
