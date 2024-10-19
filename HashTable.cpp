#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    vector<int> table;
    int currentSize;
    int numElements;
    const int EMPTY = -1;
    const double LOAD_FACTOR_THRESHOLD = 0.8;
    
    // Helper function to check if a number is prime
    bool isPrime(int num) {
        if (num <= 1) return false;
        if (num == 2 || num == 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0)
                return false;
        }
        return true;
    }

    // Helper function to find the next prime number
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Hash function
    int hashFunction(int key) {
        return key % currentSize;
    }

    // Resize function to rehash the table when threshold is exceeded
    void resize() {
        int newSize = nextPrime(currentSize * 2);
        vector<int> newTable(newSize, EMPTY);

        // Rehash all elements in the new table
        for (int i = 0; i < currentSize; i++) {
            if (table[i] != EMPTY) {
                int newHash = table[i] % newSize;
                int j = 0;
                while (newTable[(newHash + j * j) % newSize] != EMPTY) {
                    j++;
                }
                newTable[(newHash + j * j) % newSize] = table[i];
            }
        }

        table = newTable;
        currentSize = newSize;
    }

public:
    // Constructor to initialize the hash table with a given size
    HashTable(int size) {
        currentSize = nextPrime(size);
        table.resize(currentSize, EMPTY);
        numElements = 0;
    }

    // Insert function with quadratic probing
    void insert(int key) {
        if (numElements >= LOAD_FACTOR_THRESHOLD * currentSize) {
            resize();
        }

        int hash = hashFunction(key);
        int i = 0;

        while (table[(hash + i * i) % currentSize] != EMPTY) {
            if (table[(hash + i * i) % currentSize] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i++;
            if (i >= currentSize) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }

        table[(hash + i * i) % currentSize] = key;
        numElements++;
    }

    // Remove function with quadratic probing
    void remove(int key) {
        int hash = hashFunction(key);
        int i = 0;

        while (table[(hash + i * i) % currentSize] != EMPTY) {
            if (table[(hash + i * i) % currentSize] == key) {
                table[(hash + i * i) % currentSize] = EMPTY;
                numElements--;
                return;
            }
            i++;
            if (i >= currentSize) {
                cout << "Element not found" << endl;
                return;
            }
        }

        cout << "Element not found" << endl;
    }

    // Search function to return the index of the key
    int search(int key) {
        int hash = hashFunction(key);
        int i = 0;

        while (table[(hash + i * i) % currentSize] != EMPTY) {
            if (table[(hash + i * i) % currentSize] == key) {
                return (hash + i * i) % currentSize;
            }
            i++;
            if (i >= currentSize) {
                return -1;  // Key not found
            }
        }

        return -1;  // Key not found
    }

    // Print function to display the current state of the hash table
    void printTable() {
        for (int i = 0; i < currentSize; i++) {
            if (table[i] == EMPTY) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};
