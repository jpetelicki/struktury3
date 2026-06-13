#include "AVLTree.hpp"

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    destroyTree(root);
}

void AVLTree::destroyTree(AVLNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::height(AVLNode* node) const {
    if (node == nullptr) return 0;
    return node->height;
}

int AVLTree::max(int a, int b) const {
    return (a > b) ? a : b;
}

int AVLTree::getBalance(AVLNode* node) const {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

void AVLTree::insert(int key, int value) {
    root = insert(root, key, value);
}

AVLNode* AVLTree::insert(AVLNode* node, int key, int value) {
    if (node == nullptr)
        return new AVLNode(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else {
        node->value = value;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

bool AVLTree::search(int key, int& outValue) const {
    AVLNode* current = root;
    while (current != nullptr) {
        if (key == current->key) {
            outValue = current->value;
            return true;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}

AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

void AVLTree::remove(int key) {
    root = remove(root, key);
}

AVLNode* AVLTree::remove(AVLNode* node, int key) {

    if (node == nullptr) {
        return node;
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {

        if (node->left == nullptr || node->right == nullptr) {
            AVLNode* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                AVLNode* toDelete = node;
                node = temp;
                temp = toDelete;
            }
            delete temp;
        }
        else {
            AVLNode* temp = minValueNode(node->right);

            node->key = temp->key;
            node->value = temp->value;

            node->right = remove(node->right, temp->key);
        }
    }
    if (node == nullptr) {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::extractAll(int* keys, int* values, int& index) const {
    extractAll(root, keys, values, index);
}

void AVLTree::extractAll(AVLNode* node, int* keys, int* values, int& index) const {
    if (node == nullptr) return;

    extractAll(node->left, keys, values, index);

    keys[index] = node->key;
    values[index] = node->value;
    index++;

    extractAll(node->right, keys, values, index);
}