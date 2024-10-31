#include <stdio.h>

#define MAX 5

int coin[MAX];
int num[MAX];
void found (int n, int cur, int total) {
    for (int i=0;i<=total/coin[cur];i++) {
            //printf("%d     %d  %d\n", cur, i, coin[cur]);
        if (n-cur!=1) {
            num[cur] = i;
            found(n, cur+1, total-coin[cur]*i);
        }
        else {
            if (total-coin[cur]*i!=0) continue;
            num[cur] = i;
            show(n);
            break;
        }
    }
}
void show (int n) {
    printf("(%d", num[0]);
    for (int j=1;j<n;j++) printf(",%d", num[j]);
    printf(")\n");
    return;
}

int main (void) {
    //int coin[MAX], num[MAX];
    int n, total, i, j;

    scanf("%d", &n);
    for (i=0;i<n;i++)  scanf(" %d", &coin[i]);
    scanf(" %d", &total);
    found(n, 0, total);

    return 0;
}
