#pragma once

class Tests {
private:
    int sizes[8];
    int numSeeds;
    int numRepeats;

    void generateRandomData(int size, int seed, int*& values);

    void testInsert();
    void testRemove();

public:
    Tests();
    void runAllTests();
};