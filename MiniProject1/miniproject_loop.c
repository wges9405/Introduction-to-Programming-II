#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TBLSIZE 65535
#define MAXLEN 256
//lex
typedef enum {UNKNOWN, END, INT, ID, ADDSUB, MULDIV, ASSIGN,LPAREN, RPAREN, ENDFILE} TokenSet;
//paser
typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;
Symbol table[TBLSIZE];
typedef struct _Node {
    char lexeme[MAXLEN];
    TokenSet data;
    int val;
    struct _Node *left, *right;
} BTNode;
//asssss
int flag;
int i;

//lex
int match (TokenSet token);
void advance(void);
char* getLexeme(void);
TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];
//paser
int getval(void);
int setval(char *str, int val);
BTNode* makeNode(TokenSet tok, const char *lexe);
void freeTree(BTNode *root);
BTNode* factor(void);
BTNode* term(void);
BTNode* expr(void);
void statement(void);
void error();
int sbcount = 0;
//codegen
int evaluateTree(BTNode *root);

int main () {
    //freopen("input.1.txt","r",stdin);
    //freopen("input4.txt","w",stdout);
    //printf(">> ");
    while (1) {
        flag = 0;
        statement();
    }
    return 0;
}

TokenSet getToken (void) {
    int i;
    char c;

    while ( (c = fgetc(stdin)) == ' ' || c== '\t' );  // ©¿²¤ªÅ¥Õ¦r¤¸

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    }
    else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    }
    else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    }
    else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    }
    else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    }
    else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    }
    else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    }
    else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    }
    else if (c == EOF) {
        return ENDFILE;
    }
    else {
        error();
    }
}

void advance (void) {
    lookahead = getToken();
}

int match (TokenSet token) {
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

char* getLexeme (void) {
    return lexeme;
}

int getval (void) {
    int i, retval, found;

    if (match(INT)) {
        retval = atoi(getLexeme());
    }
    else if (match(ID)) {
        i = 0; found = 0; retval = 0;
        while (i<sbcount && !found) {
            if (strcmp(getLexeme(), table[i].name)==0) {
                retval = table[i].val;
                found = 1;
                break;
            }
            else {
                i++;
            }
        }
        if (!found) {
            if (sbcount < TBLSIZE) {
                strcpy(table[sbcount].name, getLexeme());
                table[sbcount].val = 0;
                sbcount++;
            }
            else {
                error();
            }
        }
    }
    return retval;
}

int setval(char *str, int val)
{
    int i, retval;
    i = 0;
    while (i<sbcount) {
        if (strcmp(str, table[i].name)==0) {
            table[i].val = val;
            retval = val;
            break;
        } else {
            i++;
        }
    }
    return retval;
}
/* create a node without any child.*/
BTNode* makeNode (TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/* clean a tree.*/
void freeTree (BTNode *root) {
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
/*factor := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN*/
BTNode* factor (void) {
    BTNode* retp = NULL;
    char tmpstr[MAXLEN];

    if (match(INT)) {
        retp =  makeNode(INT, getLexeme());
        retp->val = getval();
        advance();
    }
    else if (match(ID)) {
        BTNode* left = makeNode(ID, getLexeme());
        left->val = getval();
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ASSIGN)) {
            flag = 1;
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->right = expr();
            retp->left = left;
        }
        else if (!flag) {
            error();
        }
        else {
            retp = left;
        }
    }
    else if (match(ADDSUB)) {
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ID) || match(INT)) {
            retp = makeNode(ADDSUB, tmpstr);
            if (match(ID))
                retp->right = makeNode(ID, getLexeme());
            else
                retp->right = makeNode(INT, getLexeme());
            retp->right->val = getval();
            retp->left = makeNode(INT, "0");
            retp->left->val = 0;
            advance();
        }
        else {
            error();
        }
    }
    else if (match(LPAREN)) {
        advance();
        retp = expr();
        if (match(RPAREN)) advance();
        else error();
    }
    else
        error();
    return retp;
}
/*  term        := factor term_tail
    term_tail := MULDIV factor term_tail | NIL*/
BTNode* term (void) {
    BTNode *retp, *left;
    retp = left = factor();

    while (match(MULDIV)) {
        retp = makeNode(MULDIV, getLexeme());
        advance();
        retp->right = factor();
        retp->left = left;
        left = retp;
    }
    return retp;
}
/*  expr        := term expr_tail
  expr_tail   := ADDSUB term expr_tail | NIL*/
BTNode* expr (void) {
    BTNode *retp, *left;
    //int retval;
    retp = left = term();
    while (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->right = term();
        retp->left = left;
        left = retp;
    }
    return retp;
}
/*statement   := END | expr END*/
void statement (void) {
    BTNode* retp;
    int ans;

    if (match(ENDFILE)) {
        int i;
        for (i=0; i<3; i++) printf("MOV r%d [%d]\n", i, i*4);
        printf("EXIT 0\n");
        exit(0);
    }
    else if (match(END)) {
        advance();

    }
    else {
        if (lookahead!=ID) error();
        retp = expr();
        if (match(END)) {
            ans = evaluateTree(retp);
            i = 0;
            assemblycode(retp);
            freeTree(retp);

            advance();
        }
    }
}
void error () {
    printf("EXIT 1\n");
    exit(0);
}

void assemblycode (BTNode *root) {
    if (root!=NULL) {
        switch (root->data) {
            case ID:
                if (!strcmp(root->lexeme, "x"))
                    printf("MOV r%d [0]\n", i);
                else if (!strcmp(root->lexeme, "y"))
                    printf("MOV r%d [4]\n", i);
                else if (!strcmp(root->lexeme, "z"))
                    printf("MOV r%d [8]\n", i);
                i++;
                break;
            case INT:
                printf("MOV  r%d %d\n", i, root->val);
                i++;
                break;
            case ASSIGN:
                if (!strcmp(root->lexeme, "=")) {
                    assemblycode(root->right);
                    if (!strcmp(root->left->lexeme, "x")) {
                        printf("MOV [0] r0\n");
                        break;
                    }
                    if (!strcmp(root->left->lexeme, "y")) {
                        printf("MOV r1 r0\n");
                        printf("MOV [4] r1\n");
                        break;
                    }
                    if (!strcmp(root->left->lexeme, "z")) {
                        printf("MOV r2 r0\n");
                        printf("MOV [8] r2\n");
                        break;
                    }
                }
                break;
            case ADDSUB:
            case MULDIV:
                assemblycode(root->left);
                assemblycode(root->right);
                if (!strcmp(root->lexeme, "+")) {
                    i--;
                    printf("ADD r%d r%d\n", i-1, i);

                }
                if (!strcmp(root->lexeme, "-")) {
                    i--;
                    printf("SUB r%d r%d\n", i-1, i);
                }
                if (!strcmp(root->lexeme, "*")) {
                    i--;
                    printf("MUL r%d r%d\n", i-1, i);
                }
                if (!strcmp(root->lexeme, "/")) {
                    i--;
                    printf("DIV r%d r%d\n", i-1, i);
                }
                break;
            default:
                break;
        }
    }
}

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
            else if (strcmp(root->lexeme, "/") == 0) {
                if (root->right->data!=ID) {
                    if (!rv) error();
                    else retval = lv / rv;
                }
                else {
                    if (!rv) retval = 0;
                    else retval = lv / rv;
                }
            }
            else if (strcmp(root->lexeme, "=") == 0)
                retval = setval(root->left->lexeme, rv);
            break;
        default:
            retval = 0;
        }
    }
    return retval;
}
