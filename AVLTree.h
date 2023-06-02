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
        Node<K,V>* insert(const K &key, const V &value);
        Node<K,V>* remove(const K &key);
        void update(const K &key, const V & value);
        void prettyPrint() const {prettyPrint(root, 0);}
        bool empty() const {return (root == nullptr);}
        unsigned size() const {return numNodes;}
        void clear();
    private:
        int getBalance(Node<K,V> *node);
        int getHeight(Node<K,V> *node);
        Node<K,V>* rightRotation(Node<K,V> *y);
        Node<K,V>* leftRotation(Node<K,V> *x);
        void updateHeight(Node<K,V> *node);
        Node<K, V>* searchNode(Node<K, V>* node, const K& key) const;
        void prettyPrint(Node<K,V> *node, int level) const;
        void clear(Node<K,V> *root);
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

template<typename K, typename V>
int AVLTree<K, V>::getHeight(Node<K, V> *node) {
    if(node == nullptr)
        return 0;
    return node->h;
}


template<typename K, typename V>
int AVLTree<K, V>::getBalance(Node<K, V> *node) {
    if(node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

template<typename K, typename V>
Node<K, V>* AVLTree<K, V>::searchNode(Node<K, V>* node, const K& key) const {
    if (node == nullptr || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return searchNode(node->left, key);
    } else {
        return searchNode(node->right, key);
    }
}


template<typename K, typename V>
void AVLTree<K, V>::update(const K& key, const V& value) {
    Node<K, V>* node = searchNode(root, key);
    if (node != nullptr) {
        node->value = value;
    } else {
        cout << "Node was not found" << endl;
    }
}

template<typename K, typename V>
AVLTree<K, V>::~AVLTree() {
    clear();
}

template<typename K, typename V>
void AVLTree<K, V>::clear() {
    clear(root);
    root = nullptr;
    numNodes = 0;
}

template<typename K, typename V>
void AVLTree<K, V>::clear(Node<K, V> *root) {
    if(root == nullptr)
        return;

    if(root->left != nullptr)
        clear(root->left);
    if(root->right != nullptr)
        clear(root->right);
    delete root;
}

template<typename K, typename V>
void AVLTree<K, V>::updateHeight(Node<K, V> *node) {
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

template <typename K, typename V>
Node<K,V>* AVLTree<K, V> :: rightRotation(Node<K,V> *y) {
    Node<K,V>* x = y->left;
    y->left = x->right;
    x->right = y;
    updateHeight(y);
    updateHeight(x);

    return x;
}

template<typename K, typename V>
Node<K, V> *AVLTree<K, V>::leftRotation(Node<K, V> *x) {
    Node<K,V>* y = x->right;
    x->right = y->left;
    y->left = x;
    updateHeight(x);
    updateHeight(y);

    return y;
}


#endif //AVL_AVLTREE_H
