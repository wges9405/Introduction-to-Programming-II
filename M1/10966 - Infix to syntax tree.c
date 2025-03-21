#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM];

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;
BTNode* EXPR();
BTNode* FACTOR();
BTNode* makeNode(char c);
void freeTree(BTNode *root);
void printPrefix(BTNode *root);


BTNode* makeNode(char c) {
    BTNode *node=(BTNode*)malloc(sizeof(BTNode));
    int i;

    for (i=0; i<NUMSYM; i++)
        if (c==sym[i]) {
            node->data = i;
            break;
        }
    node->left = NULL;
    node->right = NULL;
    return node;
}
BTNode* EXPR(){
    char c;
    BTNode *node=NULL, *right=NULL;

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
            else
                node = right;
        }
        else
            node = right;
    }
    return node;
}
BTNode* FACTOR(){
    char c;
    BTNode *node=NULL;

    if (pos>=0) {
        c = expr[pos--];
        if (c>='A' && c<='D')
            node = makeNode(c);
        else if (c==')') {
            node = EXPR();
            pos--;
        }
    }
    return node;
}

int main(void){
    sym[0]='A';
    sym[1]='B';
    sym[2]='C';
    sym[3]='D';
    sym[4]='&';
    sym[5]='|';
    while (scanf("%s", expr)!=EOF)
    {
        pos = strlen(expr) - 1;
        BTNode *root = EXPR();
        printPrefix(root);
        printf("\n");
        freeTree(root);
    }

    return 0;
}

/* print a tree by pre-order. */
void printPrefix(BTNode *root){
    if (root != NULL) {
        printf("%c",sym[root->data]);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
/*
A&B|C&D&A&B|C&D
A|(B&C)|D
(((A&B)))
*/
/*
&|&&&|&ABCDABCD
||A&BCD
&AB
*/
