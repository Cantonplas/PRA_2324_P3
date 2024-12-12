#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include "Dict.h"
#include "TableEntry.h"
#include "BSTree.h"
#include <ostream>
#include <stdexcept>

template <typename V>
class BSTreeDict: public Dict<V> {


    private:
    BSTree<TableEntry<V>>* tree;


    public:
    BSTreeDict(){
        tree = new BSTree<TableEntry<V>>();
    }
    ~BSTreeDict() {
		delete tree;
	}
    
    
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
        out << *bs.tree << std::endl;
        return out;
    }

    V operator[](std::string key){
        return search(key);
    }

    int entries() override{ 
        return tree->size();
    }

    void insert(std::string key, V value) override{
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    V search(std::string key) override{
        TableEntry<V> query(key);
        TableEntry<V> result = tree->search(query);
        V value = result.value;
        return value;
    }

    V remove(std::string key) override{
        TableEntry<V> query(key);
        TableEntry<V> result = tree->search(query);
        V value = result.value;
        tree->remove(query);
        return value;
    }
};

#endif