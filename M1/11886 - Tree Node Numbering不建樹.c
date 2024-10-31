#include <stdio.h>

int height, child;
void print(int ,int, int);

int main () {
    scanf("%d %d", &height, &child);
    print(height, child, 0);
    printf("\n");
    return 0;
}

void print (int H, int C, int N) {
    int s_c = child;
    if (C<=0) return;
    if (H) {
        printf("%d ", N);
        print(H-1, s_c--, N*child+1);
        print(H-1, s_c--, N*child+2);
        print(H-1, s_c--, N*child+3);
        print(H-1, s_c--, N*child+4);
        print(H-1, s_c, N*child+5);
    }
}
