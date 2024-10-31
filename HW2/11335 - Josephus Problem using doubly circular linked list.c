#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *prev;
    int number;
    struct node *next;
}node;

node* head;
node* createList (int);
void printList (void);
int solveJosephus (int);
void freeList (void);

int main (void) {
    int n, m;

    while (scanf("%d%d", &n, &m)!=EOF) {
        head = createList(n);
        //printList();
        printf("%d\n", solveJosephus(m));
        freeList();
    }
    return 0;
}

node* createList (int n) {
    node *fir = (node*)malloc(sizeof(node)), *pre, *temp = fir;
    int i=1;

    temp->number = i;

    for (i=2; i<=n; i++) {
        temp->next = (node*)malloc(sizeof(node));
        pre = temp;
        temp = temp->next;

        temp->prev = pre;
        temp->number = i;
    }
    temp->next = fir;
    fir->prev = temp;

    return fir;
}
void printList (void){
    node *temp=head->next;
    printf("%d", head->number);
    while(temp->number != head->number) {
        printf(" %d", temp->number);
        temp = temp->next;
    }
    printf(" %d\n", temp->number);
}

int solveJosephus (int step) {
    int i, flag=1;
    node *temp, *pre, *nex;

    while (head->number != head->next->number) {
        temp = head;
        if (flag) {
            for (i=0; i<step-1; i++)  temp = temp->next;
            pre = temp->prev;
            nex = temp->next;
        //printf("  %d %d %d", pre->number, temp->number, nex->number);

            pre->next = nex;
            nex->prev = pre;

            free(temp);

            head = pre;
            //printf("  %d\n", head->number);

            flag = 0;
        }
        else {
            for (i=0; i<step-1; i++)  temp = temp->prev;
            pre = temp->prev;
            nex = temp->next;
        //printf("  %d %d %d", pre->number, temp->number, nex->number);

            pre->next = nex;
            nex->prev = pre;

            free(temp);

            head = nex;
            //printf("  %d\n", head->number);

            flag = 1;
        }
    }
    return head->number;
}

void freeList (void) {
    head->next = NULL;
    head->prev = NULL;
    free(head);
}

/*in
sample 1:
8 3

sample 2:
7 4

sample 3:
1024768 591
*/

/*out
sample 1:
2

sample 2:
3

sample 3:
584
*/
