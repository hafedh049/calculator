#include "tree.h"
#include "linked_list.h"

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

int findLowestPrecedence(LinkedList *expression, int start, int end) {
    int lowestPrec = INT_MAX;
    int lowestIndex = -1;

    Node *head = expression->head;
    int i = 0;

    while (head)
    {
         if (isOperator(head->data)) {
            int prec = (!strcmp(head->data,"+") || !strcmp(head->data,"-")) ? 1 : 2;
            if (prec <= lowestPrec) {
                lowestPrec = prec;
                lowestIndex = i;
            }
        }
        i += 1;
    }

    return lowestIndex;
}

TreeNode* buildExpressionTree(LinkedList *expression, int start, int end) {
    if (start > end)
        return NULL;

    int index = findLowestPrecedence(expression, start, end);

    if (index == -1) {
        return createNode(get(expression,start));
    }

    TreeNode* root = createNode(expression[index]);
    root->left = buildExpressionTree(expression, start, index - 1);
    root->right = buildExpressionTree(expression, index + 1, end);

    return root;
}