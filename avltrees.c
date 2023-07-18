#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}
struct Node* rotateRight(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

int getBalanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && key < node->left->key)
        return rotateRight(node);

    if (balanceFactor < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balanceFactor > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balanceFactor < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void preorderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d ", root->key);
        printf("%d ",root->key);
        preorderTraversal(root->left, file);
        preorderTraversal(root->right, file);
    }
}

void inorderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        inorderTraversal(root->left, file);
        fprintf(file, "%d ", root->key);
        printf("%d ",root->key);
        inorderTraversal(root->right, file);
    }
}

void postorderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        postorderTraversal(root->left, file);
        postorderTraversal(root->right, file);
        printf("%d ",root->key);
        fprintf(file, "%d ", root->key);
    }
}

int main() {
    struct Node* root = NULL;
    int numNodes, maxNum;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the maximum value for a node: ");
    scanf("%d", &maxNum);
    FILE* file = fopen("numbers.txt", "w");
    srand(time(0));
    for (int i = 0; i < numNodes; i++) {
        int randomNum = rand() % maxNum + 1;
        fprintf(file, "%d ", randomNum);
        printf( "%d ", randomNum);
        root = insert(root, randomNum);
    }
    fclose(file);
    file = fopen("numbers.txt", "r");
    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        root = insert(root, num);
    }
    fclose(file);
    int deleteKey;
    printf("Enter the key to delete: ");
    scanf("%d", &deleteKey);
    root = deleteNode(root, deleteKey);
    FILE* preorderFile = fopen("preorder.txt", "w");
    FILE* inorderFile = fopen("inorder.txt", "w");
    FILE* postorderFile = fopen("postorder.txt", "w");

    printf("Preorder traversal: ");
    preorderTraversal(root, preorderFile);
    fclose(preorderFile);

    printf("\nInorder traversal: ");
    inorderTraversal(root, inorderFile);
    fclose(inorderFile);

    printf("\nPostorder traversal: ");
    postorderTraversal(root, postorderFile);
    fclose(postorderFile);

    return 0;
}
