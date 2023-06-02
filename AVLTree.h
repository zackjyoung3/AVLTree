#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H
#include "Node.h"
#include <iostream>

using namespace std;

template <typename K, typename V>
    class AVLTree {
    public:
        AVLTree();
        ~AVLTree();
        void insert(const K &key, const V &value);
        void remove(const K &key);
        void update(const K &key, const V & value);
        void prettyPrint() const {prettyPrint(root, 0);}
        bool empty() const {return (root == nullptr);}
        unsigned size() const {return numNodes;}
    private:
        void rightRotation(Node<K,V> *y);
        void lefttRotation(Node<K,V> *x);
        void prettyPrint(Node<K,V> *node, int level) const;
        Node<K,V> *root;
        int numNodes;
};

template<typename K, typename V>
AVLTree<K, V>::AVLTree() {
    root = nullptr;
    numNodes = 0;
}

template<typename K, typename V>
void AVLTree<K, V>:: prettyPrint(Node<K,V> *node, int level) const {
    if (node == nullptr) {
        return;
    }

    // Increase indentation for each level
    const int indentation = 4;
    printTree(node->right, level + 1);

    // Print the current node
    for (int i = 0; i < level * indentation; ++i) {
        cout << " ";
    }
    cout << node->key << ":" << node->value << endl;

    printTree(node->left, level + 1);
}

#endif //AVL_AVLTREE_H
