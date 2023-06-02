#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree<int, int> test;
    for(int i = 1; i <= 10; i++) {
        test.insert(i,i);
        cout << test << endl << endl;
    }
    return 0;
}
