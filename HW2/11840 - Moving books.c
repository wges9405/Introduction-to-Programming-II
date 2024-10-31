#include <stdio.h>

typedef struct table{
    int number;
    int bookon[25];
}table;

table desk[25];
void create (int);
void move (int);
void pile (int);
void operate (int ,int, int, int);
void Back (int, int, int);
void Exit (int);

int main (void) {
    char str[10];
    int N;

    scanf(" %d", &N);
    create(N);
    while (scanf(" %s", str)!=EOF) {
        if (strcmp(str, "move")==0) move(N);
        else if (strcmp(str, "pile")==0) pile(N);
        else if (strcmp(str, "exit")==0) break;
    }
    Exit(N);
    return 0;
}

void create (int N) {
    int i;
    for (i=0; i<N; i++) {
        desk[i].number = 1;
        desk[i].bookon[0] = i;
    }
}

void move (int N) {
    char str[10];
    int A, B;

    scanf(" %d %s %d", &A, str, &B);
    if (A==B) return;
    if (!strcmp(str, "onto")) operate(A, B, 0, N);
    else if (!strcmp(str, "over")) operate(A, B, 1, N);
}

void pile (int N) {
    char str[10];
    int A, B;

    scanf(" %d %s %d", &A, str, &B);
    if (A==B) return;
    if (!strcmp(str, "onto")) operate(A, B, 2, N);
    else if (!strcmp(str, "over")) operate(A, B, 3, N);
}

void operate (int A, int B, int flag, int N) {
    int i, j;
    int Ai, Apos, Aall, Bi, Bpos, Ball;

    for (i=0; i<N; i++) {
        for (j=0; j<desk[i].number; j++) {
            if (desk[i].bookon[j]==A) {
                Ai = i;
                Apos = j;
            }
            if (desk[i].bookon[j]==B) {
                Bi = i;
                Bpos = j;
            }
            if (Ai==i) Aall = j+1;
            if (Bi==i) Ball = j+1;
        }
    }
    if (Ai==Bi) return;
    //printf(" %d %d %d\n %d %d %d\n", Ai, Apos, Aall, Bi, Bpos, Ball);
    if (flag==0) {
        Back(Ai, Apos, Aall);
        Back(Bi, Bpos, Ball);
        desk[Bi].bookon[Bpos+1] = desk[Ai].bookon[Apos];
        desk[Ai].number = Apos;
        desk[Bi].number = (Bpos+1)+(1);
    }
    else if (flag==1) {
        Back(Ai, Apos, Aall);
        desk[Bi].bookon[Ball] = desk[Ai].bookon[Apos];
        desk[Ai].number = Apos;
        desk[Bi].number = (Ball)+(1);
    }
    else if (flag==2) {
        Back(Bi, Bpos, Ball);
        for (i=0; i<Aall-Apos; i++) desk[Bi].bookon[(Bpos+1)+i] = desk[Ai].bookon[Apos+i];
        desk[Ai].number = Apos;
        desk[Bi].number = (Bpos+1)+(Aall-Apos);
    }
    else if (flag==3) {
        for (i=0; i<Aall-Apos; i++) desk[Bi].bookon[(Ball)+i] = desk[Ai].bookon[Apos+i];
        desk[Ai].number = Apos;
        desk[Bi].number = (Ball)+(Aall-Apos);
    }
    //Exit(N);
}

void Back (int I, int pos, int all) {
    int i;
    for (i=pos+1; i<all; i++) desk[desk[I].bookon[i]].number += 1;
}

void Exit (int N) {
    int i, j;
    for (i=0; i<N; i++) {
        printf("%d:", i, desk[i].number);
        for (j=0; j<desk[i].number; j++) printf(" %d", desk[i].bookon[j]);
        printf("\n");
    }
}
/*in
10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
exit
*/
/*out
0: 0
1: 1 9 2 4
2:
3: 3
4:
5: 5 8 7 6
6:
7:
8:
9:
*/
