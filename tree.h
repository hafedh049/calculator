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

void insert(TreeNode **, char *);

void delete_tree(TreeNode **);

void deleteNode(TreeNode **, char *);