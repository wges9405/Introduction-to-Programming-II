#include <stdio.h>

int Queen[12]={0}, Castle[12]={0}, M, N, ttl=0;

void place (int, int, int);
int valid (int, int, int);
void display(void);

int main (void) {

    scanf(" %d %d", &M, &N);
    place(1, M, N);
    printf("%d\n", ttl);

    return 0;
}


void place (row, a, b) {
    int col;

    if (row==(M+N+1)) {
        //display();
        ttl+=1;
    }
    else {
        for (col=1;col<=(M+N);col++) {
            if (valid(row, col, 1) && a) {
                Queen[row] = col;
                //printf("Q %d %d %d\n", row, Queen[row], a);
                place(row+1, a-1, b);
            }
            Queen[row] = 0;
            if (valid(row, col, 2) && b) {
                Castle[row] = col;
                //printf("C %d %d %d\n", row, Castle[row], b);
                place(row+1, a, b-1);
            }
            Castle[row] = 0;
        }
    }
}
int valid (row, col, N) {
    int i, flagQ=0, flagC=0, flagS=0;

    for (i=1;i<row;i++) {
        if ( (Queen[i]==col+row-i || Queen[i]==col-row+i) && Queen[i]!=0 ) flagQ=1;
        if ( (Castle[i]==col+row-i || Castle[i]==col-row+i) && Castle[i]!=0 ) flagC=1;
        if ( Queen[i]==col || Castle[i]==col ) flagS=1;

        if ( (flagS || flagQ || flagC) && N==1 ) return 0;
        else if ( (flagS || flagQ) && N==2 ) return 0;
    }
    return 1;
}

void display (void) {
    int row, col;
    for (row=1; row<=(M+N);row++) {
        for (col=1;col<=(M+N);col++) {
            if (Queen[row]==col)
                printf("Q");
            else if (Castle[row]==col)
                printf("C");
            else
                printf("X");
        }
        printf("\n");
    }
    printf("\n");
}
