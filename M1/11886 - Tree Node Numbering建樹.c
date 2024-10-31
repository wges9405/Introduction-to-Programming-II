#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node *a, *b, *c, *d, *e;
}Node;

int height, child;
Node *makeNode(int, int, int);
void printNode(Node*);
void freeNode(Node*);

int main () {
    scanf("%d %d", &height, &child);

    Node* node = makeNode(height, child, 0);
    printNode(node);
    printf("\n");
    freeNode(node);

    return 0;
}

Node *makeNode (H, C, N) {
    int s_c = child;
    if (C<=0) return NULL;
    if (H) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = N;
        node->a = makeNode(H-1, s_c--, N*child+1);
        node->b = makeNode(H-1, s_c--, N*child+2);
        node->c = makeNode(H-1, s_c--, N*child+3);
        node->d = makeNode(H-1, s_c--, N*child+4);
        node->e = makeNode(H-1, s_c--, N*child+5);
        return node;
    }
    else return NULL;
}

void printNode (Node *node) {
    if (node!=NULL) {
        printf("%d ", node->data);
        printNode(node->a);
        printNode(node->b);
        printNode(node->c);
        printNode(node->d);
        printNode(node->e);
    }
}

void freeNode(Node *node) {
    if (node!=NULL) {
        freeNode(node->a);
        freeNode(node->b);
        freeNode(node->c);
        freeNode(node->d);
        freeNode(node->e);
        free(node);
    }
}
