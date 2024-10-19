#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    vector<int> table;
    int currentSize;
    int threshold;
    int numElements;

    // Helper function to find next prime number
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Helper function to resize the hash table
    void resizeTable() {
        int newSize = currentSize * 2;
        while (!isPrime(newSize)) {
            newSize++;
        }

        vector<int> oldTable = table;
        table.clear();
        table.resize(newSize, -1);
        currentSize = newSize;
        numElements = 0;

        for (int value : oldTable) {
            if (value != -1) {
                insert(value);
            }
        }
    }

    // Hash function (key mod size of the table)
    int hashFunction(int key) {
        return key % currentSize;
    }

public:
    // Constructor
    HashTable(int size = 5) {
        currentSize = size;
        table.resize(currentSize, -1);
        threshold = currentSize / 2; // Resize when table is half full
        numElements = 0;
    }

    // Insert function
    void insert(int key) {
        if (numElements >= threshold) {
            resizeTable();
        }

        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;

        while (table[index] != -1) {
            if (table[index] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i++;
            index = (originalIndex + i * i) % currentSize;  // Quadratic probing
            if (i > currentSize) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }

        table[index] = key;
        numElements++;
    }

    // Remove function
    void remove(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;

        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -1;
                numElements--;
                return;
            }
            i++;
            index = (originalIndex + i * i) % currentSize;
            if (i > currentSize) {
                cout << "Element not found" << endl;
                return;
            }
        }
        cout << "Element not found" << endl;
    }

    // Search function
    int search(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;

        while (table[index] != -1) {
            if (table[index] == key) {
                return index;
            }
            i++;
            index = (originalIndex + i * i) % currentSize;
            if (i > currentSize) {
                return -1;
            }
        }
        return -1;
    }

    // Print table function
    void printTable() {
        for (int i = 0; i < currentSize; i++) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};


