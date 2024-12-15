#include <string>
#include <iostream>
#include "binary_tree.h"
#include "binary_tree_exception.h"

using namespace std;

int main() {
    try {
        BinaryTree<int> intTree({ 10, -5, 15, -2, 7, -12, 20 });
        cout << "Integer tree in order: ";
        intTree.displayInOrder();

        // Итератор по положительным элементам
        auto posIter = intTree.positiveIterator();
        cout << "Positive values: ";
        while (posIter.hasNext()) {
            cout << posIter.next() << " ";
        }
        cout << endl;

        // Итератор по отрицательным элементам
        auto negIter = intTree.negativeIterator();
        cout << "Negative values: ";
        while (negIter.hasNext()) {
            cout << negIter.next() << " ";
        }
        cout << endl;
    }
    catch (const BinaryTreeException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
