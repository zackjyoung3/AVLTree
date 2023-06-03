#ifndef AVL_NODE_H
#define AVL_NODE_H

template <typename K, typename V>
struct Node {
    Node(const K& key, const V& value)
            : key(key), value(value), left(nullptr), right(nullptr), h(1) {}
    K key;
    V value;
    Node* left;
    Node* right;
    int h;
    void copyKeyValue(Node* toCopy) {key = toCopy->key; value = toCopy->value;}
};


#endif //AVL_NODE_H
