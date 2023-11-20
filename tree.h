#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createNode(int);

void inorderTraversal(TreeNode *);

void preorderTraversal(TreeNode *);

void postorderTraversal(TreeNode *);

void insert(TreeNode **, int);

void delete_tree(TreeNode **);

void deleteNode(TreeNode **, int);

int countElements(TreeNode *);