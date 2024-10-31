#include <stdio.h>
#include <stdlib.h>

typedef struct Card{
    int number;
    struct Card *next;
} Card;

Card* read (int);
void operate (int, Card*);
Card* ADD (int, int, Card*);
Card* CUT (int, int, Card*);
void print_Card(Card*);
void free_card(Card*);

int main (void) {
    int N, M;
    int i, j;
    char ch;
    Card *cards=NULL;

    scanf("%d %d", &N, &M);

    cards = read(N);

    operate(M, cards);



    return 0;
}

Card* read (int N) {
    int i, num;
    Card *head = (Card*) malloc(sizeof(Card));;
    Card *cards;

    scanf(" %d", &num);     ///第一個
    head->number = num;
    head->next = (Card*) malloc(sizeof(Card));

    cards = head->next;

    for ( i=1; i<N-1; i++) {
        scanf(" %d", &num);
        cards->number = num;
        cards->next = (Card*) malloc(sizeof(Card));
        cards = cards->next;
    }

    scanf(" %d", &num);     ///最後一個
    cards->number = num;
    cards->next = NULL;

    return head;
}

void operate (int M, Card* cards) {
    int HT[10000][2];
    int i, j, m;
    Card *temp, *head, *tail;

    for (i=0; i<M; i++) scanf(" %d %d", &HT[i][0], &HT[i][1]);

    for (i=M-1; i>=0; i++) {
        temp = cards;
        for (j=0; j<HT[i][1]; j++)  temp = temp->next;
        head = temp->next;
        tail = head;
        for (j=HT[i][1]; j<HT[i][1]+HT[i][0]-1; j++) tail = tail->next;
        temp->next = tail->next;
        tail->next = cards;
        cards = head;
    }


    print_Card(cards);
    free_card(cards);

}

void print_Card (Card* cards) {
    while (cards!=NULL) {
        printf("%d\n", cards->number);
        cards = cards->next;
    }
}

void free_card (Card* cards) {
    Card *temp;
    while (cards!=NULL) {
        temp = cards;
        cards = cards->next;
        free(temp);
    }
}
