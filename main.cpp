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

    for(int i = 1; i <= 13; i++) {
        test.insert(i,i);
    }
    cout << "The tree has been repopulated" << endl << test << endl;

    for(int i = 13; i >= 1; i--) {
        test.remove(i);
        cout << test << endl << endl;
    }
    return 0;
}
