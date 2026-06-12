#pragma once

struct HashNode {
    int key;
    int value;
    HashNode* next; //wskaźnik na kolejny element w przypadku kolizji

    HashNode(int k, int v) : key(k), value(v), next(nullptr) {}
};

class HashTableList {
private:

    HashNode** table; //dynamiczna tablica przechowująca Hash Nody

    int capacity;
    int size;

    int hashFunction(int key) const;

    void rehash();

public:
    HashTableList(int initialCapacity);
    ~HashTableList();

    void insert(int key, int value);
    void remove(int key);
    bool search(int key, int& outValue) const;
    void print() const;
};