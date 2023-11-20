#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode
{
    char *data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createNode();

void inorderTraversal(TreeNode *);

void preorderTraversal(TreeNode *);

void postorderTraversal(TreeNode *);

void delete_tree(TreeNode **);