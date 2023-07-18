#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[100];   
    struct Node *left;      
    struct Node *right;     
    int height;             
};
int getHeight(struct Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}
struct Node *createNode(char word[]) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    strcpy(node->word, word);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}
int getBalanceFactor(struct Node *node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}
struct Node *insertWord(struct Node *root, char word[]) {
    if (root == NULL)
        return createNode(word);

    if (strcmp(word, root->word) < 0)
        root->left = insertWord(root->left, word);
    else if (strcmp(word, root->word) > 0)
        root->right = insertWord(root->right, word);
    else
        return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    int balance = getBalanceFactor(root);

    // Left Left Case
    if (balance > 1 && strcmp(word, root->left->word) < 0)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && strcmp(word, root->right->word) > 0)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && strcmp(word, root->left->word) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && strcmp(word, root->right->word) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
void inorderTraversal(struct Node *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s\n", root->word);
        inorderTraversal(root->right);
    }
}
void predictWords(struct Node *root, char prefix[]) {
    if (root == NULL)
        return;

    if (strncmp(prefix, root->word, strlen(prefix)) < 0)
        predictWords(root->left, prefix);
    else if (strncmp(prefix, root->word, strlen(prefix)) > 0)
        predictWords(root->right, prefix);
    else {
        inorderTraversal(root->right);
        printf("%s\n", root->word);
        inorderTraversal(root->left);
    }
}

int main() {
    struct Node *root = NULL;
    root = insertWord(root, "apple");
    root = insertWord(root, "banana");
    root = insertWord(root, "application");
    root = insertWord(root, "ball");
    root = insertWord(root, "bat");
    root = insertWord(root, "cat");
    root = insertWord(root, "car");
    root = insertWord(root, "cattle");

    char prefix[100];
    printf("Enter the prefix to predict words: ");
    scanf("%s", prefix);

    printf("Predicted words:\n");
    predictWords(root, prefix);

    return 0;
}
