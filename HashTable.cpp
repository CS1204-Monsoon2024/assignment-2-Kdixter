#include <iostream>  
#include <vector>  
  
class HashTable {  
private:  
   int size;  
   int threshold;  
   std::vector<int> table;  
  
   // Helper function to check if a number is prime  
   bool isPrime(int num) {  
      if (num <= 1) return false;  
      for (int i = 2; i * i <= num; i++) {  
        if (num % i == 0) return false;  
      }  
      return true;  
   }  
  
   // Helper function to find the next prime number  
   int nextPrime(int num) {  
      while (!isPrime(num)) {  
        num++;  
      }  
      return num;  
   }  
  
   // Helper function to resize the table  
   void resize() {  
      int newSize = nextPrime(size * 2);  
      std::vector<int> newTable(newSize, -1);  
      for (int i = 0; i < size; i++) {  
        if (table[i] != -1) {  
           int index = table[i] % newSize;  
           while (newTable[index] != -1) {  
              index = (index + 1) % newSize;  
           }  
           newTable[index] = table[i];  
        }  
      }  
      size = newSize;  
      table = newTable;  
   }  
  
public:  
   // Constructor  
   HashTable(int initialSize) : size(initialSize), threshold(0.8 * initialSize), table(initialSize, -1) {}  
  
   // Insert a value into the table  
   void insert(int value) {  
      if (search(value) != -1) {  
        std::cout << "Duplicate key insertion is not allowed" << std::endl;  
        return;  
      }  
      int index = value % size;  
      int probingLimit = 0;  
      while (table[index] != -1 && probingLimit < size) {  
        index = (index + 1) % size;  
        probingLimit++;  
      }  
      if (probingLimit == size) {  
        std::cout << "Max probing limit reached!" << std::endl;  
        return;  
      }  
      table[index] = value;  
      if ((double)++threshold / size >= 0.8) {  
        resize();  
      }  
   }  
  
   // Remove a value from the table  
   void remove(int value) {  
      int index = search(value);  
      if (index == -1) {  
        std::cout << "Element not found" << std::endl;  
        return;  
      }  
      table[index] = -1;  
   }  
  
   // Search for a value in the table  
   int search(int value) {  
      int index = value % size;  
      int probingLimit = 0;  
      while (table[index] != value && probingLimit < size) {  
        index = (index + 1) % size;  
        probingLimit++;  
      }  
      return probingLimit == size ? -1 : index;  
   }  
  
   // Print the table  
   void printTable() {  
      for (int i = 0; i < size; i++) {  
        if (table[i] == -1) {  
           std::cout << "- ";  
        } else {  
           std::cout << table[i] << " ";  
        }  
      }  
      std::cout << std::endl;  
   }  
};
