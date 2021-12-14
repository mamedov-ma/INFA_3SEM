#include <stdio.h>
#include <stdlib.h>
char m[1000][1000];
int main()
{
    int n, x, y, f;
    char c;
    scanf("%d", &n);
    for(int i = 0; i<999; i++)
    {
        for(int j = 0; j<999; j++)
        m[i][j] = 'N';
    }
    for(int i = 0; i<n; i++)
    {
        scanf("%d", &f);
        if(f == 1)
        {
            scanf("%d %d %c", &x, &y, &c);
            m[x][y] = c;
        }
        else
        {
            scanf("%d %d", &x, &y);
            printf("%c", m[x][y]);
        }
    }
    return 0;
}
