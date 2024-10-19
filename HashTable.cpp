#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HashTable {
private:
    vector<int> table;
    int capacity;
    int size;

    // Hash function
    int hashFunction(int key) {
        return key % capacity;
    }

    // Helper function to check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    // Helper function to get the next prime number
    int getNextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Resize the table when load factor exceeds the threshold
    void resizeTable() {
        int newCapacity = getNextPrime(2 * capacity);
        vector<int> newTable(newCapacity, -1);
        
        // Rehash all existing keys
        for (int i = 0; i < capacity; i++) {
            if (table[i] != -1) {
                int key = table[i];
                int index = key % newCapacity;
                int j = 1;
                while (newTable[index] != -1) {
                    index = (key + j * j) % newCapacity;
                    j++;
                }
                newTable[index] = key;
            }
        }
        table = newTable;
        capacity = newCapacity;
    }

public:
    HashTable(int initialCapacity) {
        capacity = initialCapacity;
        size = 0;
        table.resize(capacity, -1);  // -1 indicates an empty slot
    }

    void insert(int key) {
        if (size / (double)capacity >= 0.8) {
            resizeTable();  // Resize if load factor exceeds 0.8
        }

        int index = hashFunction(key);
        int i = 1;
        while (table[index] != -1 && table[index] != key) {
            if (i > capacity / 2) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
            index = (hashFunction(key) + i * i) % capacity;
            i++;
        }

        if (table[index] == key) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        table[index] = key;
        size++;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int i = 1;
        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -1;  // Mark the spot as empty
                size--;
                return;
            }
            index = (hashFunction(key) + i * i) % capacity;
            i++;
        }
        cout << "Element not found" << endl;
    }

    int search(int key) {
        int index = hashFunction(key);
        int i = 1;
        while (table[index] != -1) {
            if (table[index] == key) {
                return index;
            }
            index = (hashFunction(key) + i * i) % capacity;
            i++;
        }
        return -1;  // Key not found
    }

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

