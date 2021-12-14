#include <stdio.h>
#include <stdlib.h>
void foo(int *a, int k)
{
    for(int i = 0; i<k; i++)
    {
        if(a[i] % 2 == 0) a[i] = 2*a[i];
            else a[i] = a[i] + 2;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int*m = (int*)malloc(n*sizeof(int));
    for(int i = 0; i<n; i++)
    {
        scanf("%d", &m[i]);
    }
    foo(m, n);
    for(int i = 0; i<n; i++)
    {
        printf("%d ", m[i]);
    }
    free(m);
    return 0;
}
