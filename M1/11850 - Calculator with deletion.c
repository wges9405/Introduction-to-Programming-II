#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
    char data;
    struct _node *left;
    struct _node *right;
    int index;
}Node;

char expr[300000];

Node* makeNode();
int op(Node*);
void dele(int, int, Node*);
void freeNode(Node*);

int main (void) {
    int N, A, B;

    scanf("%d\n", &N);
    scanf("%s", expr);
    Node *node = makeNode();
    printf("%d\n", op(node));

    while (N--) {
        scanf(" %d %d", &A, &B);
        dele(A, B, node);
        printf("%d\n", op(node));
    }
    freeNode(node);
    return 0;
}

Node* makeNode () {
    Node* node=(Node*)malloc(sizeof(Node));
    static int pos=0;
    char c;

    c = expr[pos++];
    node->data = c;
    node->index = pos;
    if (c>='1'&&c<='9') {
        node->left = NULL;
        node->right = NULL;
    }
    else if (c=='*' || c=='+' || c=='-') {
        node->left = makeNode();
        node->right = makeNode();
    }
    return node;
}

void dele (int A, int B, Node *node) {
    if (node==NULL) return;

    if (node->index>=A && node->index<=B) node->index = 0;
    else if (node->index>B) node->index -= B-A+1;
    dele(A, B, node->left);
    dele(A, B, node->right);
}

int op (Node* node) {
    if (node==NULL) return;

    char c=node->data;
    int op1, op2;
    if (node->index!=0) {
        if (c>='1' && c<='9') {
            return c-'0';
        }
        else if (c=='*') {
            op1 = op(node->left);
            op2 = op(node->right);
            return (op1*op2)%10007;
        }
        else if (c=='+') {
            op1 = op(node->left);
            op2 = op(node->right);
            return (op1+op2)%10007;
        }
        else if (c=='-') {
            op1 = op(node->left);
            op2 = op(node->right);
            return (op1-op2)%10007;
        }
    }
    else {
        return op(node->right);
    }
}

void freeNode(Node *node) {
    if (node!=NULL) {
        freeNode(node->left);
        freeNode(node->right);
        free(node);
    }
}
