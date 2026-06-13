#include "HashTableAVL.hpp"
#include <iostream>

HashTableAVL::HashTableAVL(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;
    table = new AVLTree[capacity];
}

HashTableAVL::~HashTableAVL() {
    delete[] table;
}

int HashTableAVL::hashFunction(int key) const {
    unsigned int uKey = static_cast<unsigned int>(key);
    unsigned int alpha = 2654435769U;
    return static_cast<int>((static_cast<unsigned long long>(uKey * alpha) * capacity) >> 32);
}

void HashTableAVL::insert(int key, int value) {
    if (size >= capacity * 2) {
        rehash();
    }

    int index = hashFunction(key);
    table[index].insert(key, value);
    size++;
}

void HashTableAVL::remove(int key) {
    int index = hashFunction(key);
    table[index].remove(key);
    size--;
}

bool HashTableAVL::search(int key, int& outValue) const {
    int index = hashFunction(key);
    return table[index].search(key, outValue);
}

void HashTableAVL::rehash() {
    if (size == 0) return;

    int* allKeys = new int[size];
    int* allValues = new int[size];
    int currentIndex = 0;

    for (int i = 0; i < capacity; ++i) {
        table[i].extractAll(allKeys, allValues, currentIndex);
    }

    int oldCapacity = capacity;
    AVLTree* oldTable = table;

    capacity = oldCapacity * 2;
    table = new AVLTree[capacity];

    int totalElementsToInsert = size;
    size = 0;

    for (int i = 0; i < totalElementsToInsert; ++i) {
        insert(allKeys[i], allValues[i]);
    }

    delete[] allKeys;
    delete[] allValues;
    delete[] oldTable;
}