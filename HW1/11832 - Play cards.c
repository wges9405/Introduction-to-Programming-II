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
    int NOC, NOO;
    int i, j;
    char ch;
    Card *cards=NULL;

    scanf("%d %d", &NOC, &NOO);

    cards = read(NOC);

    operate(NOO, cards);

    return 0;
}

Card* read (int NOC) {
    int i, num;
    Card *head = (Card*) malloc(sizeof(Card));;
    Card *cards;

    scanf(" %d", &num);     ///第一個
    head->number = num;
    head->next = (Card*) malloc(sizeof(Card));

    cards = head->next;

    for ( i=1; i<NOC-1; i++) {
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

void operate (int NOO, Card* cards) {
    char ch[10];
    int i, a, b;

    for ( i=0; i<NOO; i++) {
        while (getchar()!='\n');
        fgets(ch, 4, stdin);
        scanf(" %d %d", &a, &b);
        if (ch[0] == 'A') {
            cards = ADD(a, b, cards);
        }
        else if (ch[0] == 'C') {
            cards = CUT(a, b, cards);
        }
    }
    print_Card(cards);
    free_card(cards);
}

Card* ADD (int idx, int num, Card* cards) {
    int i;
    Card *temp = (Card*) malloc(sizeof(Card)), *head=cards;

    temp->number = num;

    if (idx==0) {
        temp->next = head;
        head = temp;
    }
    else {
        for ( i=0; i<idx-1; i++)    cards = cards->next;
        temp->next = cards->next;
        cards->next = temp;
    }

    return head;
}

Card* CUT (int a, int b, Card* cards) {
    int i;
    Card *head, *tail, *temp;

    if (a==0) return cards;

    temp = cards;
    for ( i=0; i<a-1; i++)  temp = temp->next;
    head = temp->next;
    tail = head;
    for ( i=a; i<a+b-1; i++) tail = tail->next;

    temp->next = tail->next;
    tail->next = cards;

    return head;
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
