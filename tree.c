#include "tree.h"
#include "linked_list.c"

void inorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("\e[1;32m%d \e[1;33m-> \e[0m", root->data);
    inorderTraversal(root->right);
}

void preorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;
    printf("\e[1;32m%d \e[1;33m-> \e[0m", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("\e[1;32m%d \e[1;33m-> \e[0m", root->data);
}

TreeNode *createNode(char *data)
{
    struct TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void delete_tree(TreeNode **root)
{
    if (*root)
    {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        free((*root));
    }
}

int isOperator(char *c) {
    return (!strcmp(c,"+") || !strcmp(c,"-") || !strcmp(c,"*") || !strcmp(c,"/"));
}

int findLowestPrecedence(LinkedList *expression, int start, int end) {
    int lowestPrec = INT_MAX;
    int lowestIndex = -1;

    for (int i = start; i <= end; i++) {
        if (isOperator(get(expression,i))) {
            int prec = (get(expression,i) == '+' || get(expression,i) == '-') ? 1 : 2;
            if (prec <= lowestPrec) {
                lowestPrec = prec;
                lowestIndex = i;
            }
        }
    }

    return lowestIndex;
}

TreeNode* buildExpressionTree(LinkedList *expression, int start, int end) {
    if (start > end)
        return NULL;

    int index = findLowestPrecedence(expression, start, end);

    if (index == -1)
        return createNode(get(expression,start));

    TreeNode* root = createNode(get(expression,index));
    root->left = buildExpressionTree(expression, start, index - 1);
    root->right = buildExpressionTree(expression, index + 1, end);

    return root;
}