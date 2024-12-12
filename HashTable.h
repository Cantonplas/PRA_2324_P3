#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "..\Practica_1\Practica1 funcional\PRA_2425_P1\ListLinked.h"  // 

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    
    int h(const std::string& key) {
        int sum = 0;
        for (char c : key) { // esto es igual a en python for c in key
            sum += static_cast<int>(c);
        }
        return (sum % max + max) % max;
    }

public:

    HashTable(int size) {
        if (size <= 0) throw std::invalid_argument("Tamaño invalido");
        table = new ListLinked<TableEntry<V>>[size];
        max = size;
        n = 0;
    }

    ~HashTable() {
        delete[] table;
    }


    int capacity() {
        return max;
    }

    
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; i++) {
            out << i << ": " << th.table[i] << std::endl;
        }
        return out;
    }

    
    V operator[](std::string key) {
        int aux = h(key);
        for (int i = 0; i < table[aux].size(); i++) {
            if (table[aux][i].key == key) {
                return table[aux][i].value;
            }
        }
        throw std::runtime_error("Clave no encontrada");
    }


    void insert(std::string key, V value) override {
        int aux = h(key);

        for (int i = 0; i < table[aux].size(); i++) {
            if (table[aux][i].key == key) {
                throw std::runtime_error("Clave ya en uso");
            }
        }

        TableEntry<V> entry(key, value);
        table[aux].insert(0, entry); 
        n++;
    }

    V search(std::string key) override {
        int aux = h(key);
        if (table[aux].empty()) {
            throw std::runtime_error("Clave no encontrada");
        }

        for (int i = 0; i < table[aux].size(); i++) {
            if (table[aux][i].key == key) {
                return table[aux][i].value;
            }
        }
        throw std::runtime_error("Clave no encontrada");
    }

    V remove(std::string key) override {
        int aux = h(key);
        if (table[aux].empty()) {
            throw std::runtime_error("Clave no encontrada");
        }

        for (int i = 0; i < table[aux].size(); i++) {
            if (table[aux][i].key == key) {
                V val = table[aux][i].value;
                table[aux].remove(i);
                n--;
                return val;
            }
        }
        throw std::runtime_error("Clave no encontrada");
    }


    int entries() override {
        return n;
    }
};

#endif 