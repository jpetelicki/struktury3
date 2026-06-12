#include "HashTableOpen.hpp"
#include <iostream>

HashTableOpen::HashTableOpen(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;
    table = new HashNodeO[capacity];
}

HashTableOpen::~HashTableOpen() {
    delete[] table;
}

int HashTableOpen::hashFunction(int key) const {
    unsigned int uKey = static_cast<unsigned int>(key);
    unsigned int alpha = 2654435769U; //stała 2^32/(złoty podział)

    unsigned int hash = (static_cast<unsigned long long>(uKey * alpha) * capacity) >> 32;

    return static_cast<int>(hash);
}

void HashTableOpen::rehash() {
    int oldCapacity = capacity;
    HashNodeO* oldTable = table;

    capacity = oldCapacity * 2;
    table = new HashNodeO[capacity];
    size = 0;

    for (int i = 0; i < oldCapacity; ++i) {
        if (oldTable[i].status == Status::OCCUPIED) {
            insert(oldTable[i].key, oldTable[i].value);
        }
    }

    delete[] oldTable;
}

void HashTableOpen::insert(int key, int value) {
    if (size >= capacity * 0.7) {
        rehash();
    }

    int index = hashFunction(key);
    int firstDeleted = -1;

    while (table[index].status != Status::EMPTY) {
        if (table[index].status == Status::OCCUPIED && table[index].key == key) {
            table[index].value = value;
            return;
        }

        if (table[index].status == Status::DELETED && firstDeleted == -1) {
            firstDeleted = index;
        }

        index = (index + 1) % capacity;
    }

    if (firstDeleted != -1) {
        index = firstDeleted;
    }

    table[index].key = key;
    table[index].value = value;
    table[index].status = Status::OCCUPIED;
    size++;
}

void HashTableOpen::remove(int key) {
    int index = hashFunction(key);

    while (table[index].status != Status::EMPTY) {
        if (table[index].status == Status::OCCUPIED && table[index].key == key) {
            table[index].status = Status::DELETED;
            size--;
            return;
        }
        index = (index + 1) % capacity;
    }
}

bool HashTableOpen::search(int key, int& outValue) const {
    int index = hashFunction(key);

    while (table[index].status != Status::EMPTY) {
        if (table[index].status == Status::OCCUPIED && table[index].key == key) {
            outValue = table[index].value;
            return true;
        }
        index = (index + 1) % capacity;
    }
    return false;
}

void HashTableOpen::print() const {
    for (int i = 0; i < capacity; ++i) {
        std::cout << "[" << i << "] ";
        if (table[i].status == Status::OCCUPIED) {
            std::cout << "Klucz: " << table[i].key << " | Wartość: " << table[i].value;
        }
        else if (table[i].status == Status::DELETED) {
            std::cout << "--- USUNIĘTY ---";
        }
        else {
            std::cout << "--- PUSTY ---";
        }
        std::cout << "\n";
    }
}