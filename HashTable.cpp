#include <iostream>
#include <vector>

using namespace std;

// Function for primality
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to find the next prime number greater than or equal to a given number
int nextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

class HashTable {
private:
    vector<int> table;   // Vector to represent the hash table
    int tableSize;       // Size of the hash table
    int numElements;     // Number of elements currently in the table
    const double threshold = 0.8; // Load factor

    // Hashing function
    int hash(int key) {
        return key % tableSize;
    }

    // Resizing function
    void resizeTable() {
        int newSize = nextPrime(tableSize * 2);  // Resize to at least double the previous size, and a prime number
        vector<int> newTable(newSize, -1);
        
        // Rehash existing elements once resized
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != -1) {
                int newIndex = table[i] % newSize;
                int j = 0;
                while (newTable[(newIndex + j * j) % newSize] != -1) {
                    j++;
                }
                newTable[(newIndex + j * j) % newSize] = table[i];
            }
        }
        table = newTable;
        tableSize = newSize;
    }

public:
    // Constructor
    HashTable(int size) {
        tableSize = nextPrime(size);  // Initial size should be a prime number
        table.resize(tableSize, -1);  // Initialize table with -1 representing empty slots (NULL)
        numElements = 0;
    }

    // Insert function
    void insert(int key) {
        if ((double)numElements / tableSize >= threshold) {
            resizeTable();
        }

        int index = hash(key);
        int j = 0;
        
        // duplicate insertion
        for (int i = 0; i < tableSize; i++) {
            int probedIndex = (index + j * j) % tableSize;
            if (table[probedIndex] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            if (table[probedIndex] == -1) break;
            j++;
        }

        j = 0;
        while (j < tableSize) {
            int probedIndex = (index + j * j) % tableSize;
            if (table[probedIndex] == -1) {
                table[probedIndex] = key;
                numElements++;
                return;
            }
            j++;
        }
        
        cout << "Max probing limit reached!" << endl;
    }

    // Remove function
    void remove(int key) {
        int index = hash(key);
        int j = 0;
        while (j < tableSize) {
            int probedIndex = (index + j * j) % tableSize;
            if (table[probedIndex] == key) {
                table[probedIndex] = -1; // Mark the slot as empty
                numElements--;
                return;
            }
            if (table[probedIndex] == -1) break; // Stop if an empty slot is found
            j++;
        }
        cout << "Element not found" << endl;
    }

    // Search function
    int search(int key) {
        int index = hash(key);
        int j = 0;
        while (j < tableSize) {
            int probedIndex = (index + j * j) % tableSize;
            if (table[probedIndex] == key) {
                return probedIndex;
            }
            if (table[probedIndex] == -1) break; // Stop if an empty slot is found
            j++;
        }
        return -1; // Not found
    }

    // Printing the hash table
    void printTable() {
        for (int i = 0; i < tableSize; i++) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};

// Example main program
int main() {
    HashTable ht(7);  // Start with table size 7
    
    ht.insert(2);
    ht.insert(17);
    ht.printTable();  // Expected output: "- - - 2 - 17 - "

    ht.insert(19);
    ht.printTable();  // Resizing might occur depending on the threshold

    ht.remove(17);
    ht.printTable();  // Expected output: "- - - 2 - - - "

    int index = ht.search(2);
    cout << "Index of 2: " << index << endl;

    return 0;
}