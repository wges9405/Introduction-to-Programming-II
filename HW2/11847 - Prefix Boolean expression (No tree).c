#include <stdio.h>
#include <string.h>

#define max_expr 30
#define max_seq 6

char expr[max_expr];
int seq[max_seq-2];
int len, idx=0;

void work (int);
int operate (void);

int main (void) {

    scanf("%s", expr);
    len = strlen(expr);
    work(0);
    printf("%d %d %d %d %d\n", seq[0], seq[1], seq[2], seq[3], operate());
    return 0;
}

void work (int cur) {
    int i;

    for (i=cur; i<max_seq-2; i++) {
        seq[i] = 0;
        work(i+1);
        printf("%d %d %d %d %d\n", seq[0], seq[1], seq[2], seq[3], operate());
        idx = 0;
        seq[i] = 1;
    }
}

int operate() {
    int op1, op2;
    if (idx==len) return;
    switch (expr[idx++]) {
        case 'A':
            return seq[0];
        case 'B':
            return seq[1];
        case 'C':
            return seq[2];
        case 'D':
            return seq[3];
        case '&':
            op1 = operate();
            op2 = operate();
            return op1&op2;
        case '|':
            op1 = operate();
            op2 = operate();
            return op1|op2;
        default:
            return ;
    }
}
/*
|&AC|AB
*/
/*
0 0 0 0 0
0 0 0 1 0
0 0 1 0 0
0 0 1 1 0
0 1 0 0 1
0 1 0 1 1
0 1 1 0 1
0 1 1 1 1
1 0 0 0 1
1 0 0 1 1
1 0 1 0 1
1 0 1 1 1
1 1 0 0 1
1 1 0 1 1
1 1 1 0 1
1 1 1 1 1
*/
