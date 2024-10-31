#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head);
void printInfix (Node *root) {
    static int flag=0;

    if (root!=NULL) {
        if (root->data>='A' && root->data <='D') {
            printInfix(root->left);
            printf("%c", root->data);
            printInfix(root->right);
        }
        else if (!flag) {
            printInfix(root->left);
            printf("%c", root->data);
            if (root->right->data=='&' || root->right->data=='|') flag=1;
            printInfix(root->right);
        }
        else if (flag) {
            printf("(");

            flag=0;
            printInfix(root->left);
            printf("%c", root->data);
            if (root->right->data=='&' || root->right->data=='|') flag=1;
            printInfix(root->right);
            flag=0;

            printf(")");
        }
    }
}
void freeTree(Node *root);

#endif
