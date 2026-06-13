#pragma once

struct AVLNode {
    int key;
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k, int v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) const;
    int getBalance(AVLNode* node) const;
    int max(int a, int b) const;

    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

    AVLNode* insert(AVLNode* node, int key, int value);
    AVLNode* remove(AVLNode* node, int key);

    AVLNode* minValueNode(AVLNode* node);

    void extractAll(AVLNode* node, int* keys, int* values, int& index) const;

    void destroyTree(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(int key, int value);
    void remove(int key);
    bool search(int key, int& outValue) const;
    void extractAll(int* keys, int* values, int& index) const;

    AVLNode* getRoot() const { return root; }
};