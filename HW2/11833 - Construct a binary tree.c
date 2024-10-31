#include <stdlib.h>
#include <stdio.h>

typedef struct _node {
    int value;
    struct _node *left;
    struct _node *right;
} Node;

int inorder[200000], preorder[200000], inpos[200000];
Node *build (int, int);
Node *create_node(int);
void postorder (Node*);
void destroy (Node*);

int main (void) {
    Node *root;
    int N, value;
    int i;

    scanf("%d", &N);

    for (i=0; i<N; i++) {
        scanf(" %d", &inorder[i]);
        inpos[inorder[i]] = i;
    }
    for (i=0; i<N; i++) scanf(" %d", &preorder[i]);

    root = build(0, N-1);

    postorder(root);
    printf("\n");
    destroy(root);

    return 0;
}

Node *build (int inorder_start, int inorder_end) {
    static int preorder_idx=0;
    int inorder_idx;
    Node *root = NULL;

    if (inorder_start > inorder_end) return root;
    else root = create_node(preorder[preorder_idx++]);

    if (inorder_start != inorder_end) {
        inorder_idx = inpos[preorder[preorder_idx-1]];

        root->left = build(inorder_start, inorder_idx-1);
        root->right = build(inorder_idx+1, inorder_end);
    }

    return root;
}

Node *create_node (int value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void postorder (Node *root) {
    if (root!=NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
}

void destroy(Node *root) {
    if (root!=NULL) {
        destroy(root->left);
        destroy(root->right);
        free(root);
    }
}
/*
15
7 12 14 4 2 8 5 9 1 3 10 6 15 13 11
1 2 4 7 12 14 5 8 9 3 6 10 11 13 15
*/
/*
14 12 7 4 8 9 5 2 10 15 13 11 6 3 1
*/

/* in
9
3 7 8 6 11 2 5 4 9
2 7 3 6 8 11 5 9 4
*/
/* out
3 8 11 6 7 4 9 5 2
*/

/* in
10
7 8 4 1 5 6 2 0 9 3
7 3 9 0 2 6 5 1 4 8
*/
/* out
8 4 1 5 6 2 0 9 3 7
*/
