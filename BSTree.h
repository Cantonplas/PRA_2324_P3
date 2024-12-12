#ifndef BSTREE_H
#define BSTREE_H

#include <stdexcept>
#include <ostream>
#include "BSNode.h"

template <typename T>
class BSTree {
    private:
        BSNode<T>* root;
        int nelem;

        
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado");
            } else if (n->elem < e){
                return search(n->right, e); 

            } else if (n->elem > e){
                return search(n->left, e);
            
            } else {
                return n;
            
            }
        }

        BSNode<T>* insert(BSNode<T>* n, T e) {
            BSNode<T>* newNode = new BSNode<T>(e);
            if(n == nullptr){
                return newNode;

            }else if(n->elem == e) {
                throw std::runtime_error("El elemento ya existe");

            }else if (n->elem < e){
                n->right = insert(n->right, e);

            } else{
                n->left = insert(n->left, e);

            }
                return n;
        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            
            }
        }

        BSNode<T>* remove(BSNode<T>* n, T e) {
            if(n == nullptr){
                throw std::runtime_error("Elemento no encontrado");
            
            } else if (n->elem < e){
                n->right = remove(n->right, e);
            
            } else if (n-> elem > e){
                n->left = remove(n->left, e);
            
            } else {
                if(n->left != nullptr && n->right != nullptr){
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                
                } else {
                    n = (n->left != nullptr) ? n->left: n->right; 
            
                }
                }
            return n;
        }

        T max(BSNode<T>* n) const {
            if (n == nullptr){
                throw std::runtime_error("Elemento no encontrado");
            
            } else if (n->right != nullptr) {
                return max(n->right);
            
            } else {
                return n->elem;
            
            }
        }

        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr){
                return n->left;
                
            } else {
                n->right = remove_max(n->right);
                return n;

            }
            }

            void delete_cascade(BSNode<T>* n) {
                if (n != nullptr) {
                    delete_cascade(n->left);
                    delete_cascade(n->right);
                    delete n;
                }
        }

    public:
        BSTree(){
            root = nullptr;
            nelem = 0;
        
        }

        ~BSTree() {
            delete_cascade(root);
        }


        int size() const {
            return nelem;
        }

        T search(T e) const {
            BSNode<T>* result = search(root, e);
            return result->elem;
        }

        
        T operator[](T e) const {
            return search(e);
        }

    
        void insert(T e) {
            root = insert(root, e);
        }

        
        void remove(T e) {
            root = remove(root, e);
        }

        
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }
};

#endif