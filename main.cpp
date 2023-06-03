#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree<int, int> test;
    for(int i = 1; i <= 13; i++) {
        test.insert(i,i);
        cout << test << endl << endl;
    }
    test.update(12, 15);
    cout << test;
    test.clear();
    cout << test;
    return 0;
}
