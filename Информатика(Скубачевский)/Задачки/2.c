#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, k, c;
    k = 0;
    scanf("%d", &n);
    int*m = (int*)malloc(n*sizeof(int));
    for(int i = 0; i<n; i++)
    {
        scanf("%d", &m[i]);
        k = k + m[i];
    }
    c = k/n;
    for(int i = 0; i<n; i++)
    {
        m[i] = c - m[i];
        printf("%d ", m[i]);
    }
    free(m);
    return 0;
}
