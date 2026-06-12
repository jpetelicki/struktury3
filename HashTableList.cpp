#include "HashTableList.hpp"
#include <iostream>

HashTableList::HashTableList(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;

    table = new HashNode * [capacity];

    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

HashTableList::~HashTableList() {
    for (int i = 0; i < capacity; ++i) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* nextNode = current->next;
            delete current;
            current = nextNode;            //usuwanie wszystkich list utworzonych w węźle
        }
    }
    delete[] table;
}

int HashTableList::hashFunction(int key) const {
    unsigned int uKey = static_cast<unsigned int>(key);
    unsigned int alpha = 2654435769U;
    unsigned int hash = (static_cast<unsigned long long>(uKey * alpha) * capacity) >> 32;
    return static_cast<int>(hash);
}

void HashTableList::rehash() {
    int oldCapacity = capacity;
    HashNode** oldTable = table;

    capacity = oldCapacity * 2;
    table = new HashNode * [capacity];
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }

    for (int i = 0; i < oldCapacity; ++i) {
        HashNode* current = oldTable[i];
        while (current != nullptr) {
            HashNode* nextNode = current->next;

            int newIndex = hashFunction(current->key);

            current->next = table[newIndex];
            table[newIndex] = current;

            current = nextNode;
        }
    }
    delete[] oldTable;
}

void HashTableList::insert(int key, int value) {

    if (size >= capacity) {
        rehash();
    }

    int index = hashFunction(key);
    HashNode* current = table[index];


    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    HashNode* newNode = new HashNode(key, value);
    newNode->next = table[index];
    table[index] = newNode;
    size++;
}

void HashTableList::remove(int key) {
    int index = hashFunction(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {

            if (prev == nullptr) {
                table[index] = current->next;
            }
            else {
                prev->next = current->next;
            }

            delete current;
            size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

bool HashTableList::search(int key, int& outValue) const {
    int index = hashFunction(key);
    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            outValue = current->value;
            return true;
        }
        current = current->next;
    }
    return false;
}

void HashTableList::print() const {
    for (int i = 0; i < capacity; ++i) {
        std::cout << "[" << i << "] ";
        HashNode* current = table[i];
        if (current == nullptr) {
            std::cout << "--- PUSTY ---";
        }
        else {
            while (current != nullptr) {
                std::cout << "{" << current->key << ":" << current->value << "} -> ";
                current = current->next;
            }
            std::cout << "nullptr";
        }
        std::cout << "\n";
    }
}