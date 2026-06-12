#pragma once

enum class Status { EMPTY, OCCUPIED, DELETED };

struct HashNodeO {
    int key;
    int value;
    Status status;

    HashNodeO() : key(0), value(0), status(Status::EMPTY) {}
};

class HashTableOpen {
private:
    HashNodeO* table;
    int capacity;
    int size;

    int hashFunction(int key) const;

    void rehash();

public:
    HashTableOpen(int initialCapacity);

    ~HashTableOpen();

    void insert(int key, int value);
    void remove(int key);

    bool search(int key, int& outValue) const;
    void print() const;
};