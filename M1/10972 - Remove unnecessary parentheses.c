#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM]={'A', 'B', 'C', 'D', '&', '|'};

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;

BTNode *EXPR();
BTNode *FACTOR();
BTNode *makeNode(char);
void printInfix(BTNode*);
void freeTree(BTNode*);

int main (void) {
    scanf("%s", expr);
    pos = strlen(expr)-1;
    BTNode *root = EXPR();
    printInfix(root);
    freeTree(root);
    return 0;
}

BTNode *EXPR() {
    BTNode *node=NULL, *right=NULL;
    char c;

    if (pos>=0) {
        right = FACTOR();

        if (pos>0) {
            c = expr[pos];
            if (c=='&' || c=='|') {
                node = makeNode(c);
                node->right = right;
                pos--;
                node->left = EXPR();
            }
            else node = right;
        }
        else node = right;

    }

    return node;
}
BTNode *FACTOR() {
    BTNode *node=NULL;
    char c;

    if (pos>=0) {
        c = expr[pos--];
        if (c>='A' && c<='D')
            node = makeNode(c);
        else if (c==')') {
            node = EXPR();
            if (expr[pos--]!='(')
                freeTree(node);
        }
    }
    return node;
}

BTNode *makeNode(char c) {
    BTNode *node=(BTNode*)malloc(sizeof(BTNode));
    int i;
    for (i=0; i<NUMSYM; i++) {
        if (c==sym[i]) {
            node->data = i;
            break;
        }
    }
    node->left = NULL;
    node->right = NULL;
    return node;
}

void printInfix(BTNode * root) {
    static int flag=0;

    if (root!=NULL) {
        if (root->data>=0 && root->data <=3) {
            printInfix(root->left);
            printf("%c", sym[root->data]);
            printInfix(root->right);
        }
        else if (!flag) {
            printInfix(root->left);
            printf("%c", sym[root->data]);
            if (root->right->data==4 || root->right->data==5) flag=1;
            printInfix(root->right);
        }
        else if (flag) {
            printf("(");

            flag=0;
            printInfix(root->left);
            printf("%c", sym[root->data]);
            if (root->right->data==4 || root->right->data==5) flag=1;
            printInfix(root->right);
            flag=0;

            printf(")");
        }
    }
}

void freeTree(BTNode *root) {
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
