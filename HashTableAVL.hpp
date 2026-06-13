#pragma once
#include "AVLTree.hpp" 

class HashTableAVL {
private:
    AVLTree* table;
    int capacity;
    int size;

    int hashFunction(int key) const;
    void rehash();

public:
    HashTableAVL(int initialCapacity);
    ~HashTableAVL();

    void insert(int key, int value);
    void remove(int key);
    bool search(int key, int& outValue) const;
    void print() const;
};