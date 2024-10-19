#include <iostream>
#include <vector>

using namespace std;

// Helper function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Helper function to find the next prime number greater than a given number
int nextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

class HashTable {
private:
    vector<int> table;
    int currentSize;
    int capacity;
    const float threshold = 0.8;

    // Hash function (modulo)
    int hash(int key) {
        return key % capacity;
    }

    // Rehash the table when threshold is exceeded
    void rehash() {
        vector<int> oldTable = table;
        int oldCapacity = capacity;
        capacity = nextPrime(capacity * 2); // Resize to a prime number greater than double the current size
        table.assign(capacity, -1); // Reset table with new capacity
        currentSize = 0;

        // Reinsert the old elements
        for (int i = 0; i < oldCapacity; ++i) {
            if (oldTable[i] != -1) {
                insert(oldTable[i]);
            }
        }
    }

public:
    // Constructor
    HashTable(int size) {
        capacity = nextPrime(size);  // Ensure initial capacity is prime
        table.assign(capacity, -1);  // Initialize with -1 (empty slots)
        currentSize = 0;
    }

    // Insert function using quadratic probing
    void insert(int key) {
        int index = hash(key);
        int originalIndex = index;
        int i = 0;

        // Check if duplicate key
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        while (table[index] != -1) {
            index = (originalIndex + i * i) % capacity;
            i++;
            if (i >= capacity) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }

        table[index] = key;
        currentSize++;

        // Resize if load factor exceeds threshold
        if ((float)currentSize / capacity >= threshold) {
            rehash();
        }
    }

    // Remove function using quadratic probing
    void remove(int key) {
        int index = hash(key);
        int originalIndex = index;
        int i = 0;

        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -1;  // Mark as deleted
                currentSize--;
                return;
            }
            index = (originalIndex + i * i) % capacity;
            i++;
            if (i >= capacity) {
                break;
            }
        }

        cout << "Element not found" << endl;
    }

    // Search function using quadratic probing
    int search(int key) {
        int index = hash(key);
        int originalIndex = index;
        int i = 0;

        while (table[index] != -1) {
            if (table[index] == key) {
                return index;
            }
            index = (originalIndex + i * i) % capacity;
            i++;
            if (i >= capacity) {
                break;
            }
        }
        return -1; // Not found
    }

    // Print the table
    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};
