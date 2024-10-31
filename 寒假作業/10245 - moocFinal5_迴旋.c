#include <stdio.h>

int main (void) {
    int M, N, P;
    int row, column;
    int flag, flag2;

    while (scanf(" %d %d %d", &M, &N, &P) != EOF) {
        row=1;
        column=0;
        flag=1;
        flag2=0;
        M-=1;
        while (P>0) {
            if (flag==1) {
                P-=N;
                column+=N;
                N-=1;
                flag=2;
                if (P<0) flag2=1;
            }
            else if (flag==2) {
                P-=M;
                row+=M;
                M-=1;
                flag=3;
                if (P<0) flag2=2;
            }
            else if (flag==3) {
                P-=N;
                column-=N;
                N-=1;
                flag=4;
                if (P<0) flag2=3;
            }
            else if (flag==4) {
                P-=M;
                row-=M;
                M-=1;
                flag=1;
                if (P<0) flag2=4;
            }
        }
        while (P) {
            P+=1;
            if (flag2==1) {
                column-=1;
            }
            else if (flag2==2) {
                row-=1;
            }
            else if (flag2==3) {
                column+=1;
            }
            else if (flag2==4) {
                row+=1;
            }
        }
        printf("%d %d\n", row, column);
    }
    return 0;
}
