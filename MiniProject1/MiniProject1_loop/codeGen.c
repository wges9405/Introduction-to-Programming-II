#include <stdio.h>
#include <string.h>
#include "codeGen.h"
int r[3];
int i;
void assemblycode (BTNode *root) {
    if (root!=NULL) {
        switch (root->data) {
            case ID:
                break;
            case INT:
                printf("MOV  r%d %d\n", i++, root->val);
                break;
            case ASSIGN:
            case ADDSUB:
            case MULDIV:
                assemblycode(root->left);
                assemblycode(root->right);
                if (!strcmp(root->lexeme, "+")){
                    r[i-1] += r[i];
                    printf("ADD");
                }
                if (!strcmp(root->lexeme, "-"))
                    printf("SUB");
                if (!strcmp(root->lexeme, "*"))
                    printf("MUL");
                if (!strcmp(root->lexeme, "/"))
                    printf("DIV");
                break;
            default:
                break;
        }
    }
}
/*
int evaluateTree(BTNode *root)
{
    int retval = 0, lv, rv;
    if (root != NULL)
    {
        switch (root->data)
        {
        case ID:
        case INT:
            retval = root->val;
            break;
        case ASSIGN:
        case ADDSUB:
        case MULDIV:
            lv = evaluateTree(root->left);
            rv = evaluateTree(root->right);
            if (strcmp(root->lexeme, "+") == 0)
                retval = lv + rv;
            else if (strcmp(root->lexeme, "-") == 0)
                retval = lv - rv;
            else if (strcmp(root->lexeme, "*") == 0)
                retval = lv * rv;
            else if (strcmp(root->lexeme, "/") == 0)
                retval = lv / rv;
            else if (strcmp(root->lexeme, "=") == 0)
                retval = setval(root->left->lexeme, rv);
            break;
        default:
            retval = 0;
        }
    }
    return retval;
}

*/
// print a tree by pre-order.

void printPrefix(BTNode *root)
{
    if (root != NULL)
    {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
