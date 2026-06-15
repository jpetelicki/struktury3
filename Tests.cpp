#include "Tests.hpp"
#include "Timer.hpp"
#include "HashTableOpen.hpp"
#include "HashTableList.hpp"
#include "HashTableAVL.hpp"

#include <iostream>
#include <fstream>
#include <random>
#include <string>

Tests::Tests() {
    int defaultSizes[8] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
    for (int i = 0; i < 8; ++i) {
        sizes[i] = defaultSizes[i];
    }
    numSeeds = 10;
    numRepeats = 10;
}

void Tests::generateRandomData(int size, int seed, int*& values) {
    values = new int[size];
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> valDist(1, 2000000000);

    for (int i = 0; i < size; ++i) {
        values[i] = valDist(gen);
    }
}

void Tests::testInsert() {
    int multipliers[] = { 1, 2 };
    std::string modeNames[] = { "*1", "*2" };

    for (int m = 0; m < 2; ++m) {
        int mult = multipliers[m];
        std::cout << "\n--- Test: insert() [10x10] - Pojemnosc: " << modeNames[m] << " (" << mult << ") ---\n";

        std::ofstream file("wyniki_insert_" + modeNames[m] + ".csv");
        file << "Rozmiar;AdresowanieOtwarte;Lista;AVL\n";
        Timer timer;

        for (int sizeIndex = 0; sizeIndex < 8; ++sizeIndex) {
            int currentSize = sizes[sizeIndex];
            long long totalOpen = 0, totalList = 0, totalAVL = 0;

            for (int s = 0; s < numSeeds; ++s) {
                int* vals;
                generateRandomData(currentSize + 1, s, vals);

                std::mt19937 genTest(s + 500);
                std::uniform_int_distribution<int> valDist(1, 2000000000);

                for (int r = 0; r < numRepeats; ++r) {
                    HashTableOpen openTable(currentSize * mult);
                    HashTableList listTable(currentSize * mult);
                    HashTableAVL avlTable(currentSize * mult);

                    for (int i = 0; i < currentSize; ++i) {
                        openTable.insert(vals[i], vals[i]);
                        listTable.insert(vals[i], vals[i]);
                        avlTable.insert(vals[i], vals[i]);
                    }
                    int newKey = valDist(genTest);

                    timer.start(); openTable.insert(newKey, newKey); timer.stop();
                    totalOpen += timer.getNanoseconds();

                    timer.start(); listTable.insert(newKey, newKey); timer.stop();
                    totalList += timer.getNanoseconds();

                    timer.start(); avlTable.insert(newKey, newKey); timer.stop();
                    totalAVL += timer.getNanoseconds();
                }
                delete[] vals;
            }

            int totalMeasurements = numSeeds * numRepeats;
            long long avgOpen = totalOpen / totalMeasurements;
            long long avgList = totalList / totalMeasurements;
            long long avgAVL = totalAVL / totalMeasurements;

            std::cout << currentSize << "\t| O: " << avgOpen << " ns\t| L: " << avgList << " ns\t| A: " << avgAVL << " ns\n";
            file << currentSize << ";" << avgOpen << ";" << avgList << ";" << avgAVL << "\n";
        }
        file.close();
    }
}

void Tests::testRemove() {
    int multipliers[] = { 1, 2 };
    std::string modeNames[] = { "*1", "*2" };

    for (int m = 0; m < 2; ++m) {
        int mult = multipliers[m];
        std::cout << "\n--- Test: remove() [10x10] - Pojemnosc: " << modeNames[m] << " (" << mult << ") ---\n";

        std::ofstream file("wyniki_remove_" + modeNames[m] + ".csv");
        file << "Rozmiar;AdresowanieOtwarte;Lista;AVL\n";
        Timer timer;

        for (int sizeIndex = 0; sizeIndex < 8; ++sizeIndex) {
            int currentSize = sizes[sizeIndex];
            long long totalOpen = 0, totalList = 0, totalAVL = 0;

            for (int s = 0; s < numSeeds; ++s) {
                int* vals;
                generateRandomData(currentSize, s, vals);

                std::mt19937 genTest(s + 1000);
                std::uniform_int_distribution<int> indexDist(0, currentSize - 1);

                for (int r = 0; r < numRepeats; ++r) {
                    HashTableOpen openTable(currentSize * mult);
                    HashTableList listTable(currentSize * mult);
                    HashTableAVL avlTable(currentSize * mult);

                    for (int i = 0; i < currentSize; ++i) {
                        openTable.insert(vals[i], vals[i]);
                        listTable.insert(vals[i], vals[i]);
                        avlTable.insert(vals[i], vals[i]);
                    }

                    int randomIndex = indexDist(genTest);
                    int targetToRemove = vals[randomIndex];

                    timer.start(); openTable.remove(targetToRemove); timer.stop();
                    totalOpen += timer.getNanoseconds();

                    timer.start(); listTable.remove(targetToRemove); timer.stop();
                    totalList += timer.getNanoseconds();

                    timer.start(); avlTable.remove(targetToRemove); timer.stop();
                    totalAVL += timer.getNanoseconds();
                }
                delete[] vals;
            }

            int totalMeasurements = numSeeds * numRepeats;
            long long avgOpen = totalOpen / totalMeasurements;
            long long avgList = totalList / totalMeasurements;
            long long avgAVL = totalAVL / totalMeasurements;

            std::cout << currentSize << "\t| O: " << avgOpen << " ns\t| L: " << avgList << " ns\t| A: " << avgAVL << " ns\n";
            file << currentSize << ";" << avgOpen << ";" << avgList << ";" << avgAVL << "\n";
        }
        file.close();
    }
}

void Tests::runAllTests() {
    std::cout << "Badanie\n";
    testInsert();
    testRemove();
    std::cout << "\nKoniec\n";
}