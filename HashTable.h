#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "..\Practica_1\Practica1 funcional\PRA_2425_P1\ListLinked.h"  // 

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>* table;

    public:
        int h(std::string key) {
            int hashValue = 0;
            for (char c : key) {
                hashValue += static_cast<int>(c);
            }
            return hashValue % max;
        }

        HashTable(int size){
            table = new ListLinked<TableEntry<V>>[size];
            n = 0;
            max = size;
        }

        ~HashTable(){
            delete[] table;
        }

        int capacity(){
            return max;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
            out << "[";
            for (int i = 0; i < th.max; ++i) {
                out << th.table[i];
                if (i < th.max - 1) {
                    out << ", ";
                }
            }
            out << "]";
            return out;
        }

        V operator[](std::string key) {
            int pos = h(key);
            int index = table[pos].search(TableEntry<V>(key));
            if (index == -1) {
                throw std::out_of_range("Key not found");
            }
            return table[pos].get(index).value;
        }
        
        void insert(std::string key, V value) override{
            int pos = h(key);
            int index = table[pos].search(TableEntry<V>(key));
            if (index == -1) {
                table[pos].append(TableEntry<V>(key, value));
                n++;
            } else {
                throw std::runtime_error("Key already exists");
            }
        }

        V search(std::string key) override{
            int pos = h(key);
            int index = table[pos].search(TableEntry<V>(key));
            if (index == -1) {
                throw std::out_of_range("Key not found");
            }
            return table[pos].get(index).value;
        }

        V remove(std::string key) override{
            int pos = h(key);
            int index = table[pos].search(TableEntry<V>(key));
            if (index == -1) {
                throw std::out_of_range("Key not found");
            }
            V value = table[pos].get(index).value;
            table[pos].remove(index);
            n--;
            return value;
        }

        int entries() override{
            return n;
        }
       
        
};

#endif