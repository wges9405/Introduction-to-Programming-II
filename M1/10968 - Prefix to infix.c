#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head);
void printInfix(Node *root);
void freeTree(Node *root);

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

void constructTree(Node** head)
{
    char c;

    if((*head)==NULL)
    {
        (*head) = (Node *)malloc(sizeof(Node));
		c = getchar();

		(*head)->data = c;

        (*head)->left = (*head)->right = NULL;

        if((*head)->left == NULL && ((*head)->data=='&' || (*head)->data=='|'))
            constructTree( &(*head)->left);
        if((*head)->right == NULL && ((*head)->data=='&' || (*head)->data=='|'))
            constructTree( &(*head)->right);
    }
}

void freeTree(Node *root)
{
    if (root!=NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void)
{
    int n;
    scanf("%d", &n);// the number of test cases

    while(n>0)
    {
        getchar();
        Node *root=NULL;
        constructTree(&root);// construct syntax tree
        printInfix(root);// you have to implement this function
        printf("\n");
        freeTree(root);
        --n;
    }

    return 0;
}
/*
4
||A&BCD
||BC&|AB&CD
&A|BC
&||BC&AD||CB&AB
*/
/*
A|(B&C)|D
B|C|(A|B&(C&D))
A&(B|C)
B|C|(A&D)&(C|B|(A&B))
*/
