#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table; // Stores the keys
    std::vector<bool> occupied; // To check if a slot is occupied
    int currentSize; // Number of elements in the hash table
    int tableSize; // Current size of the table

    // Prime numbers to use for resizing
    const int primes[9] = {7, 13, 19, 31, 61, 127, 251, 509, 1021};

    // Function to get the next prime number greater than the current size
    int getNextPrime(int size) {
        for (int prime : primes) {
            if (prime > size) {
                return prime;
            }
        }
        return size * 2 + 1; // Fallback if we exceed known primes
    }

    // Hash function
    int hash(int key) {
        return key % tableSize;
    }

    // Resize the hash table
    void resize() {
        int newSize = getNextPrime(tableSize * 2);
        std::vector<int> newTable(newSize, -1);
        std::vector<bool> newOccupied(newSize, false);
        
        // Rehash all existing elements
        for (int i = 0; i < tableSize; ++i) {
            if (occupied[i]) {
                insertIntoNewTable(newTable, newOccupied, table[i]);
            }
        }
        
        // Replace old table with new table
        table = std::move(newTable);
        occupied = std::move(newOccupied);
        tableSize = newSize;
    }

    // Helper function to insert into the new table during resize
    void insertIntoNewTable(std::vector<int>& newTable, std::vector<bool>& newOccupied, int key) {
        int index = hash(key);
        int i = 0;
        while (newOccupied[index]) {
            index = (index + i * i) % newTable.size();
            ++i;
        }
        newTable[index] = key;
        newOccupied[index] = true;
    }

public:
    HashTable(int size = 7) : tableSize(size), currentSize(0) {
        table.resize(size, -1);
        occupied.resize(size, false);
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (currentSize >= tableSize * 0.8) {
            resize();
        }

        int index = hash(key);
        int i = 0;
        while (occupied[index]) {
            index = (index + i * i) % tableSize;
            ++i;
        }
        table[index] = key;
        occupied[index] = true;
        ++currentSize;
    }

    // Search for a key and return its index
    int search(int key) {
        int index = hash(key);
        int i = 0;

        while (occupied[index]) {
            if (table[index] == key) {
                return index; // Key found
            }
            index = (index + i * i) % tableSize;
            ++i;
        }
        return -1; // Key not found
    }

    // Remove a key from the hash table
    void remove(int key) {
        int index = search(key);
        if (index != -1) {
            occupied[index] = false; // Mark as deleted
            currentSize--;
        }
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < tableSize; ++i) {
            if (occupied[i]) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl; // Print a newline at the end
    }
};

int main() {
    HashTable ht;

    ht.insert(2);
    ht.insert(17);
    ht.insert(23);
    ht.insert(14);
    
    ht.printTable(); // Example output: - - - 2 - - 17 -

    std::cout << "Index of 17: " << ht.search(17) << std::endl; // Output the index
    std::cout << "Index of 100: " << ht.search(100) << std::endl; // Not found example

    ht.remove(17);
    ht.printTable(); // Should not contain 17 anymore

    return 0;
}
