#include <stdio.h>

#define MAX 10
int arr[MAX][MAX];

int big (int x, int y) {
    int  i, j, Nx, Ny, num=0;

    for (i=x;i<x+3;i++) {
        for (j=y;j<y+3;j++) {
            if (arr[i][j]>num) {
                Nx = i;
                Ny = j;
                num = arr[i][j];
            }
        }
        j-=3;
    }

    return arr[Nx][Ny];
}

int main (void) {
    int Narr[8][8];
    int n, x, y;

    scanf("%d", &n);
    for (x=0;x<n;x++) {
        for (y=0;y<n;y++) {
            scanf(" %d", &arr[x][y]);
        }
    }
    for (x=0;x<n-2;x++) {
        for (y=0;y<n-2;y++) {
            Narr[x][y] = big(x, y);
            if (y!=n-3) printf("%d ", Narr[x][y]);
            else printf("%d\n", Narr[x][y]);
        }
    }
    return 0;
}
