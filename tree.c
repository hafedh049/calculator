#include "tree.h"

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

TreeNode *createNode()
{
    struct TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = "";
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void insert(TreeNode **root, char *value)
{

    if (!(*root))
    {
        TreeNode *tmp = NULL;
        tmp = (TreeNode *)malloc(sizeof(TreeNode));
        tmp->left = tmp->right = NULL;
        tmp->data = value;
        *root = tmp;
        return;
    }
    if (value < (*root)->data)
        insert(&((*root)->left), value);
    else if (value > (*root)->data)
        insert(&((*root)->right), value);
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

void deleteNode(TreeNode **root, int key)
{
    if (*root == NULL)
        return;

    if (key < (*root)->data)
        deleteNode(&((*root)->left), key);
    else if (key > (*root)->data)
        deleteNode(&((*root)->right), key);
    else
    {
        if ((*root)->left == NULL)
        {
            TreeNode *temp = (*root)->right;
            free(*root);
            *root = temp;
        }
        else if ((*root)->right == NULL)
        {
            TreeNode *temp = (*root)->left;
            free(*root);
            *root = temp;
        }
        else
        {
            TreeNode *temp = findMinValueNode((*root)->right);
            (*root)->data = temp->data;
            deleteNode(&((*root)->right), temp->data);
        }
    }
}

void printTree(TreeNode* root, int space) {
    if (root == NULL) return;

    space += 5;

    printTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("\e[1;32m%d\e[0m", root->data);

    printTree(root->left, space);
}

int isOperator(char *c) {
    return (!strcmp(c,"+") || !strcmp(c,"-") || !strcmp(c,"*") || !strcmp(c,"/"));
}

int findLowestPrecedence(char* expression, int start, int end) {
    int lowestPrec = INT_MAX;
    int lowestIndex = -1;

    for (int i = start; i <= end; i++) {
        if (isOperator(expression[i])) {
            int prec = (expression[i] == '+' || expression[i] == '-') ? 1 : 2;
            if (prec <= lowestPrec) {
                lowestPrec = prec;
                lowestIndex = i;
            }
        }
    }

    return lowestIndex;
}

TreeNode* buildExpressionTree(char* expression, int start, int end) {
    if (start > end)
        return NULL;

    int index = findLowestPrecedence(expression, start, end);

    if (index == -1) {
        return createNode(expression[start]);
    }

    TreeNode* root = createNode(expression[index]);
    root->left = buildExpressionTree(expression, start, index - 1);
    root->right = buildExpressionTree(expression, index + 1, end);

    return root;
}