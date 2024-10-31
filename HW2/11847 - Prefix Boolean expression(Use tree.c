#include <stdio.h>
#include <stdlib.h>

#define max_exp 30
#define max_seq 6

char exp[max_exp];
typedef enum {A, B, C, D, AND, OR}TokenSet;
char sequence[max_seq]="ABCD&|";
int seq[max_seq-2];
typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} Node;

Node* preorder (void);
Node* makeNode (char);
int operate (Node*);
void work (Node*, int);
void freeTree(Node*);

int main (void) {
    Node *root;
    scanf("%s", exp);
    root = preorder();
    work(root, 0);
    printf("%d %d %d %d %d\n", seq[0], seq[1], seq[2], seq[3], operate(root));
    freeTree(root);
    return 0;
}

Node* preorder (void) {
    static int pos=0;
    Node *node;

    if (exp[pos]>='A' && exp[pos]<='D') return makeNode(exp[pos++]);
    else {
        node = makeNode(exp[pos++]);
        node->left = preorder();
        node->right = preorder();
        return node;
    }
}

Node* makeNode(char c) {
    int i;
    Node *node = (Node*) malloc(sizeof(Node));
    for (i=0; i<max_seq; i++)
        if (c==sequence[i]){
            node->data = i;
            break;
        }
    node->left = NULL;
    node->right = NULL;
    return node;
}

void work (Node* root, int cur) {
    int i;
    for (i=cur; i<max_seq-2; i++) {
        seq[i] = 0;
        work(root , i+1);
        printf("%d %d %d %d %d\n", seq[0], seq[1], seq[2], seq[3], operate(root));

        seq[i] = 1;
    }
}

int operate (Node* root) {
    if (root==NULL) return;

    int op1 = operate(root->left);
    int op2 = operate(root->right);

    if (root->data==4)
        return op1&op2;
    else if (root->data==5)
        return op1|op2;
    else
        return seq[root->data];
}

void freeTree(Node *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
