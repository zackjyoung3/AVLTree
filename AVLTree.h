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
        void prettyPrint() const;
        bool empty() const {return (root == nullptr);}
        unsigned size() const {return numNodes;}
        void clear();
        friend std::ostream& operator<<(std::ostream& os, const AVLTree& tree) {
            tree.prettyPrint();
            return os;
        }
    private:
        int getBalance(Node<K,V> *node);
        int getHeight(Node<K,V> *node);
        Node<K,V>* rightRotation(Node<K,V> *y);
        Node<K,V>* leftRotation(Node<K,V> *x);
        void updateHeight(Node<K,V> *node);
        Node<K,V>* insert(Node<K,V> *node, const K &key, const V &value);
        Node<K, V>* searchNode(Node<K, V>* node, const K& key) const;
        void prettyPrint(Node<K,V> *node, int level) const;
        void clear(Node<K,V> *root);
        Node<K,V>* remove(Node<K,V> *node, const K &key);
        Node<K,V>* deleteNodeZeroOrOneChild(Node<K,V> *node);
        Node<K,V>* deleteNodeTwoChildren(Node<K,V> *node);
        Node<K,V>* getImmediateSuccessor(Node<K,V> *node);
        Node<K,V>* getSmallestInSubtree(Node<K,V> *node);
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
    prettyPrint(node->right, level + 1);

    // Print the current node
    for (int i = 0; i < level * indentation; ++i) {
        cout << " ";
    }
    cout << node->key << ":" << node->value << endl;

    prettyPrint(node->left, level + 1);
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
    node->h = std::max(getHeight(node->left), getHeight(node->right)) + 1;
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

template<typename K, typename V>
void AVLTree<K, V>::insert(const K &key, const V &value) {
    root = insert(root, key, value);
}

template<typename K, typename V>
Node<K, V> *AVLTree<K, V>::insert(Node<K, V> *node, const K &key, const V &value) {
    // first perform normal BST insertion routine
    if(node == nullptr)
        return new Node<K,V>(key, value);
    if(key < node->key)
        node->left = insert(node->left, key, value);
    else if(key > node->key)
        node->right = insert(node->right, key, value);
    else
        return node;

    // at this point we have to update the height of the ancestor node that we are currently at
    updateHeight(node);

    // get the balance factor
    int bf = getBalance(node);

    // finally, we must ensure that this node has not become unbalanced
    // if it has, we will perform the appropriate ops to remedy the imbalance

    // left left case
    if(bf > 1 && key < node->left->key)
        return rightRotation(node);

    // right right case
    if(bf < -1 && key > node->right->key)
        return leftRotation(node);

    // left right case
    if(bf > 1 && key > node->left->key) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    // right left case
    if(bf < -1 && key < node->right->key) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    // only get here if there has been no changes
    return node;
}

template<typename K, typename V>
void AVLTree<K, V>::prettyPrint() const {
    if(root != nullptr)
        prettyPrint(root, 0);
    else
        cout << "Empty AVL Tree" << endl;
}

template<typename K, typename V>
void AVLTree<K, V>::remove(const K &key) {
    root = remove(root, key);
}

template<typename K, typename V>
Node<K,V>* AVLTree<K, V>::deleteNodeZeroOrOneChild(Node<K, V> *node) {
    Node<K,V> *child = node->left ? node->left : node->right;

    // the current node has no children so we can go ahead and delete it
    if(child == nullptr) {
        delete node;
        return nullptr;
        cout << "here" << endl;
    }
    // case where we have exactly one child
    // => dereference pointers and copy the contents of the child into the current node
    *node = *child;
    delete child;
    return node;
}

// finds the immediate successor of a node
template<typename K, typename V>
Node<K, V> *AVLTree<K, V>::getImmediateSuccessor(Node<K, V> *node) {
    return getSmallestInSubtree(node->right);
}

// helper method that is used in getImmediateSuccessor
template<typename K, typename V>
Node<K, V> *AVLTree<K, V>::getSmallestInSubtree(Node<K, V> *node) {
    if(node->left == nullptr)
        return node;
    return getSmallestInSubtree(node->left);
}

template<typename K, typename V>
Node<K,V>* AVLTree<K, V>::deleteNodeTwoChildren(Node<K, V> *node) {
    // find the immediate succesor of this node
    Node<K,V> *immediateSuccessor = getImmediateSuccessor(node);

    // copy everything from the immediate successor into this node
    node->copyKeyValue(immediateSuccessor);

    // now go into the right subtree and delete the immediate successor node
    node->right = remove(node->right, immediateSuccessor->key);
    return node;
}

template<typename K, typename V>
Node<K, V> *AVLTree<K, V>::remove(Node<K,V> *node, const K &key) {
    // as in insertion, the first part to be performed is standard BST, removal
    if(node == nullptr)
        return node;
    else if(key < node->key)
        node->left = remove(node->left, key);
    else if(key > node->key)
        node->right = remove(node->right, key);
    // case where we have key == node->key and thus, this is the key that is to be deleted
    else {
        if(node->left == nullptr || node->right == nullptr) {
            node = deleteNodeZeroOrOneChild(node);
        } else {
            node = deleteNodeTwoChildren(node);
        }
    }

    if(node == nullptr)
        return node;

    // update the height of the current node
    updateHeight(node);

    // get the balance factor
    int bf = getBalance(node);

    // now have to handle the cases of if this node has become unbalanced

    // left left case
    if(bf > 1 && getBalance(node->left) >= 0)
        return rightRotation(node);
    // right right case
    if(bf < -1 && getBalance(node->right) <= 0)
        return leftRotation(node);
    // left right case
    if(bf > 1 && getBalance(node->left) < 0) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    // right left case
    if(bf < -1 && getBalance(node->right) > 0) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}


#endif //AVL_AVLTREE_H
