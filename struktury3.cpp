#include <iostream>
#include "HashTableOpen.hpp"
#include "HashTableList.hpp"
#include "HashTableAVL.hpp"
#include "Tests.hpp"

using namespace std;

void manualTesting() {
    int structChoice;
    cout << "\n--- TESTY MANUALNE ---\n";
    cout << "Wybierz strukture do testow:\n";
    cout << "1. Tablica z Adresowaniem Otwartym\n";
    cout << "2. Kubełki z Lista Jednokierunkowa\n";
    cout << "3. Kubełki z Drzewem AVL\n";
    cout << "Wybór: ";
    cin >> structChoice;

    if (structChoice < 1 || structChoice > 3) {
        cout << "Nieprawidlowy wybor.\n";
        return;
    }

    int capacity;
    cout << "Podaj poczatkowa pojemnosc struktury: ";
    cin >> capacity;

    HashTableOpen* openTable = nullptr;
    HashTableList* listTable = nullptr;
    HashTableAVL* avlTable = nullptr;

    if (structChoice == 1) openTable = new HashTableOpen(capacity);
    else if (structChoice == 2) listTable = new HashTableList(capacity);
    else if (structChoice == 3) avlTable = new HashTableAVL(capacity);

    int opChoice = -1;
    while (opChoice != 0) {
        cout << "\n--- OPERACJE ---\n";
        cout << "1. Dodaj element (insert)\n";
        cout << "2. Usun element (remove)\n";
        cout << "0. Powrot do menu glownego\n";
        cout << "Wybór: ";
        cin >> opChoice;

        if (opChoice == 1) {
            int key, value;
            cout << "Podaj klucz: ";
            cin >> key;
            cout << "Podaj wartosc: ";
            cin >> value;

            if (openTable) openTable->insert(key, value);
            else if (listTable) listTable->insert(key, value);
            else if (avlTable) avlTable->insert(key, value);

            cout << "Dodano (" << key << ", " << value << ").\n";
        }
        else if (opChoice == 2) {
            int key;
            cout << "Podaj klucz do usuniecia: ";
            cin >> key;

            if (openTable) openTable->remove(key);
            else if (listTable) listTable->remove(key);
            else if (avlTable) avlTable->remove(key);

            cout << "Wyslano zadanie usuniecia klucza: " << key << ".\n";
        }
    }


    delete openTable;
    delete listTable;
    delete avlTable;
}

int main() {
    int mainChoice = -1;

    while (mainChoice != 0) {
        cout << "\n=====================================\n";
        cout << "  STRUKTURY DANYCH - TABLICE MIESZAJACE\n";
        cout << "=====================================\n";
        cout << "1. Uruchom testy wydajnosciowe (generowanie plikow .csv)\n";
        cout << "2. Uruchom testy manualne (interaktywne dodawanie/usuwanie)\n";
        cout << "0. Zakoncz program\n";
        cout << "Wybor: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            cout << "\nUruchamianie testow wydajnosciowych...\n";
            Tests tests;
            tests.runAllTests(); 
            cout << "Testy zakonczone pomyslnie.\n";
            break;
        }
        case 2: {
            manualTesting();
            break;
        }
        case 0: {
            cout << "Zamykanie programu...\n";
            break;
        }
        default: {
            cout << "Nieznana opcja. Sprobuj ponownie.\n";
            break;
        }
        }
    }

    return 0;
}