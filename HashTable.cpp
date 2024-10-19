#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int count;

    int hashFunction(int key) {
        return key % size;
    }

    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i <= std::sqrt(num); i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    int nextPrime(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    void resize() {
        int oldSize = size;
        size = nextPrime(2 * size);
        std::vector<int> newTable(size, -1);
        
        for (int i = 0; i < oldSize; i++) {
            if (table[i] != -1) {
                insert(table[i]); // Re-insert the elements
            }
        }
        table.swap(newTable);
    }

public:
    HashTable(int initialSize) : size(nextPrime(initialSize)), count(0) {
        table.resize(size, -1);
    }

    void insert(int key) {
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        if (count >= size / 2) {
            resize();
        }

        int index = hashFunction(key);
        int probingLimit = 0;
        
        while (probingLimit < size) {
            if (table[index] == -1) { // Empty slot found
                table[index] = key;
                count++;
                return;
            } else {
                probingLimit++;
                index = (index + probingLimit * probingLimit) % size; // Quadratic probing
            }
        }
        
        std::cout << "Max probing limit reached!" << std::endl;
    }

    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            std::cout << "Element not found" << std::endl;
            return;
        }
        table[index] = -1;
        count--;
    }

    int search(int key) {
        int index = hashFunction(key);
        int probingLimit = 0;

        while (probingLimit < size) {
            if (table[index] == -1) {
                return -1; // Key not found
            } 
            if (table[index] == key) {
                return index; // Key found
            }
            probingLimit++;
            index = (index + probingLimit * probingLimit) % size; // Quadratic probing
        }

        return -1; // Key not found after probing
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl; // New line at the end
    }
};


