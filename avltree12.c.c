#include <stdio.h>
#include <stdlib.h>
typedef struct Location {
    double latitude;
    double longitude;
} Location;
typedef struct AVLNode {
    Location location;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;
int getHeight(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
AVLNode* createNode(Location location) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->location = location;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Perform a right rotation
AVLNode* rotateRight(AVLNode* z) {
    AVLNode* y = z->left;
    AVLNode* T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = 1 + max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Perform a left rotation
AVLNode* rotateLeft(AVLNode* z) {
    AVLNode* y = z->right;
    AVLNode* T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = 1 + max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}
int getBalance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}
AVLNode* insertLocation(AVLNode* root, Location location) {
    if (root == NULL)
        return createNode(location);

    if (location.latitude < root->location.latitude)
        root->left = insertLocation(root->left, location);
    else
        root->right = insertLocation(root->right, location);

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Perform balancing if needed
    if (balance > 1 && location.latitude < root->left->location.latitude)
        return rotateRight(root);

    if (balance < -1 && location.latitude > root->right->location.latitude)
        return rotateLeft(root);

    if (balance > 1 && location.latitude > root->left->location.latitude) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && location.latitude < root->right->location.latitude) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Search for a location in the AVL tree
AVLNode* searchLocation(AVLNode* root, double latitude, double longitude) {
    if (root == NULL || root->location.latitude == latitude && root->location.longitude == longitude)
        return root;

    if (latitude < root->location.latitude)
        return searchLocation(root->left, latitude, longitude);
    else
        return searchLocation(root->right, latitude, longitude);
}

// In-order traversal of the AVL tree
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Latitude: %.6lf, Longitude: %.6lf\n", root->location.latitude, root->location.longitude);
        inorderTraversal(root->right);
    }
}
int main() {
    AVLNode* root = NULL;

    // Insert locations into the AVL tree
    root = insertLocation(root, (Location){51.5074, -0.1278}); 
    root = insertLocation(root, (Location){40.7128, -74.0060});
    root = insertLocation(root, (Location){37.7749, -122.4194});
    root = insertLocation(root, (Location){48.8566, 2.3522});
    printf("Sorted Locations:\n");
    inorderTraversal(root);
    double searchLatitude = 37.7749;
    double searchLongitude = -122.4194;
    AVLNode* foundLocation = searchLocation(root, searchLatitude, searchLongitude);
    if (foundLocation != NULL) {
        printf("Location found: Latitude: %.6lf, Longitude: %.6lf\n", foundLocation->location.latitude, foundLocation->location.longitude);
    } else {
        printf("Location not found.\n");
    }

    return 0;
}
