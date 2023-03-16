#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <cstddef>
#include <vector>
#include <iostream>

template <typename KeyType, typename ValueType>
class TreeMultimap {
    private:
        struct Node {
            Node (const KeyType& k, const ValueType& v) : key(k), left(nullptr), right(nullptr){
            values.push_back(v);
            }

            KeyType key;
            std::vector<ValueType> values;
            Node* left;
            Node* right;
        };

        Node* m_root; 

        void insertInOrder(Node* p, KeyType key, ValueType value ){
            if (m_root == nullptr){   
                m_root = new Node(key, value);   
                return; 
            }

            Node *ptr = m_root;
            for (;;) {
                if (key == ptr -> key){
                    ptr -> values.push_back(value);
                    return;
                }   

                if (key < ptr -> key) {
                    if (ptr->left != nullptr)      
                        ptr = ptr -> left;
                    else {
                        ptr -> left = new Node(key, value);
                        return;
                    }
                }
                else if (key > ptr -> key) {
                    if (ptr -> right != nullptr)     
                        ptr  = ptr -> right;
                    else {
                        ptr -> right = new Node(key, value);
                        return;
                    }
                }
            }
        }

        Node* findNode(KeyType key) const {
            Node *ptr = m_root;
            while (ptr != nullptr){ 
                if (key == ptr->key) 
                    return ptr;
                else if (key < ptr -> key)
                    ptr = ptr -> left;
                else
                    ptr = ptr -> right;
            }
            return nullptr;
        }

        void deleteTree(Node* p){
            //delete tree
            if (p == nullptr)
                return;
            deleteTree(p -> left);
            deleteTree(p -> right);
            delete p;
        }

    public:
        class Iterator {
            public:
                Iterator() {
                    m_iteratorList = nullptr;  //create invalid iterator
                    m_isValid = false;
                }

                Iterator(Node* iteratorNode) {
                    m_iteratorList = &(iteratorNode -> values);
                    m_iterator = m_iteratorList -> begin();
                    m_isValid = true;
                }


                ValueType& get_value() const {
                    return *m_iterator;
                }

                bool is_valid() const {
                    return m_isValid;
                }

                void advance() {
                    m_iterator ++;
                    if (m_iterator == m_iteratorList -> end()){
                        m_isValid = false;
                        return;
                    }
                }

            private:
                typename std::vector<ValueType>::iterator m_iterator;   //stores list and iterator to list
                std::vector<ValueType>* m_iteratorList;
                bool m_isValid;
        };

        TreeMultimap() {
            m_root = nullptr;
        }

        ~TreeMultimap() {
            deleteTree(m_root);
        }

        void insert(const KeyType& key, const ValueType& value) {
            insertInOrder(m_root, key, value);
        }

        Iterator find(const KeyType& key) const {
            Node *ptr = findNode(key);

            if (!ptr)
                return Iterator();

            return Iterator(ptr);
        }
    };

#endif // TREEMULTIMAP_INCLUDED