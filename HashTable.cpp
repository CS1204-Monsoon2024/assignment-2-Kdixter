#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    int* table;           // Pointer to the hash table
    int m;                // Current size of the table
    int count;            // Number of elements in the table
    const double loadFactorThreshold = 0.8;  // Load factor threshold
    static const int primeSize[12]; // List of prime numbers

    // Hash function
    int hash(int key) {
        return key % m;
    }

    // Function to find the next prime size for resizing
    int getNextPrimeSize(int currentSize) {
        for (int prime : primeSize) {
            if (prime > currentSize) {
                return prime;
            }
        }
        return currentSize; // Return current size if no prime is found (unlikely)
    }

    // Resize the table
    void resize() {
        int newSize = getNextPrimeSize(m * 2);
        int* newTable = new int[newSize];
        std::fill(newTable, newTable + newSize, -1); // Initialize new table with -1

        // Rehash all keys into the new table
        for (int i = 0; i < m; i++) {
            if (table[i] != -1) {
                insert(table[i]);
            }
        }

        delete[] table; // Delete old table
        table = newTable; // Point to new table
        m = newSize; // Update current size
    }

public:
    // Initialize the static array
    static const int primeSize[12];

    // Constructor
    HashTable(int size) {
        m = getNextPrimeSize(size); // Ensure initial size is prime
        table = new int[m];
        std::fill(table, table + m, -1); // Initialize table with -1
        count = 0; // Initialize element count
    }

    // Destructor
    ~HashTable() {
        delete[] table; // Free allocated memory
    }

    // Insert function
    void insert(int key) {
        if ((double)count / m >= loadFactorThreshold) {
            resize(); // Resize if load factor exceeds threshold
        }

        int idx = hash(key);
        int i = 0;

        // Quadratic probing to find the next available slot
        while (table[(idx + i * i) % m] != -1) {
            i++;
        }
        
        table[(idx + i * i) % m] = key; // Insert the key
        count++; // Increment element count
    }

    // Remove function
    void remove(int key) {
        int idx = hash(key);
        int i = 0;

        // Quadratic probing to find the key
        while (table[(idx + i * i) % m] != -1) {
            if (table[(idx + i * i) % m] == key) {
                table[(idx + i * i) % m] = -1; // Mark as deleted
                count--; // Decrement element count
                return;
            }
            i++;
        }
    }

    // Search function
    int search(int key) {
        int idx = hash(key);
        int i = 0;

        // Quadratic probing to find the key
        while (table[(idx + i * i) % m] != -1) {
            if (table[(idx + i * i) % m] == key) {
                return (idx + i * i) % m; // Return the index
            }
            i++;
        }
        return -1; // Key not found
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < m; i++) {
            if (table[i] != -1) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl; // Print new line at the end
    }
};

// Definition of the static prime size array
const int HashTable::primeSize[12] = {7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}; 

int main() {
    HashTable ht(7); // Initialize hash table with size 7

    ht.insert(2);
    ht.insert(17);
    ht.insert(15);
    ht.insert(8);
    
    ht.printTable(); // Print the current table

    std::cout << "Index of 17: " << ht.search(17) << std::endl; // Search for key 17
    ht.remove(17); // Remove key 17
    std::cout << "Index of 17 after removal: " << ht.search(17) << std::endl; // Search for key 17 after removal
    
    ht.printTable(); // Print the table after deletion

    return 0;
}
