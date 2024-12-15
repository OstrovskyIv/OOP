#include "binary_tree.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
    try {
        BinaryTree<int> intTree = { 10, 5, 15, 2, 7, 12, 20 };
        cout << "Integer tree in order: ";
        intTree.displayInOrder();

        BinaryTree<string> stringTree = { "apple", "banana", "cherry", "date" };
        cout << "String tree in order: ";
        stringTree.displayInOrder();

        stringTree.insert("banana");
    }
    catch (const BinaryTreeException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
