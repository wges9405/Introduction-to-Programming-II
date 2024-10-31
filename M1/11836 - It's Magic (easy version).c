#include <stdio.h>
#include <stdbool.h>

int grammar[100][100];
int grammar_size[100];
int sentence[100];
int pos, lenth;
int N, M;

bool solve(int);

int main (void) {
    int i, j;
    int temp;

    scanf(" %d %d", &N, &M);

    for (i=0; i<N; i++) {
        j=0;
        while (scanf(" %d", &temp) && temp!=-1)
            grammar[i][j++] = temp;
        if (grammar[i][0]==0 && j==1) {
            N--;
            i--;
            continue;
        }
        grammar[i][j] = -1;
        grammar_size[i] = j;
    }

    for (i=0; i<M; i++) {
        j=0;
        while (scanf(" %d", &temp) && temp!=-1)
            sentence[j++] = temp;
        sentence[j] = -1;
        lenth = j;
        pos = 0;
        if (solve(lenth-1)) printf("True\n");
        else printf("False\n");
    }

    return 0;
}

bool solve(int rightBound) {
    int i, j;
    int s_pos=pos;

    for (i=0; i<N; i++) {
        pos = s_pos;
        for (j=0; grammar[i][j]!=-1 && pos<=rightBound; j++) {
            if (grammar[i][j]==0){
                if (!solve(rightBound-(grammar_size[i]-(j+1))))
                    break;
            }
            else if (sentence[pos] != grammar[i][j])
                break;
            else
                pos++;
        }
        if (grammar[i][j]==-1 && pos==rightBound+1)
            return true;
    }
    return false;
}
