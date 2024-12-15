#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "node.h"
#include "binary_tree_exception.h"
#include "binary_tree_iterator.h"
#include <iostream>
#include <initializer_list>
#include <memory>
#include <sstream>
#include <type_traits>

using std::string;
using std::cout;
using std::shared_ptr;
using std::make_shared;


template<typename U>
string toString(const U& value) {
    if constexpr (std::is_arithmetic<U>::value) {
        return std::to_string(value);
    }
    else {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
}

template<typename T>
class BinaryTree {
private:
    shared_ptr<Node<T>> root;

    void copyTree(shared_ptr<Node<T>>& dest, const shared_ptr<Node<T>>& source) {
        if (source) {
            dest = make_shared<Node<T>>(source->value);
            copyTree(dest->left, source->left);
            copyTree(dest->right, source->right);
        }
    }

    void inorderTraversal(const shared_ptr<Node<T>>& node) const {
        if (node) {
            inorderTraversal(node->left);
            cout << node->value << " ";
            inorderTraversal(node->right);
        }
    }

    bool insertNode(const shared_ptr<Node<T>>& current, const T& value) {
        if (!current) return false;

        if (value < current->value) {
            if (current->left) {
                return insertNode(current->left, value);
            }
            else {
                current->left = make_shared<Node<T>>(value);
                return true;
            }
        }
        else if (value > current->value) {
            if (current->right) {
                return insertNode(current->right, value);
            }
            else {
                current->right = make_shared<Node<T>>(value);
                return true;
            }
        }

        return false;
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(initializer_list<T> initList) : BinaryTree() {
        for (const auto& value : initList) {
            insert(value);
        }
    }

    BinaryTree(const BinaryTree& other) : root(nullptr) {
        copyTree(root, other.root);
    }

    BinaryTree(BinaryTree&& other) noexcept : root(move(other.root)) {}

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            root.reset();
            copyTree(root, other.root);
        }
        return *this;
    }

    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this != &other) {
            root = move(other.root);
        }
        return *this;
    }

    void insert(const T& value) {
        if (!root) {
            root = make_shared<Node<T>>(value);
        }
        else if (!insertNode(root, value)) {
            throw BinaryTreeException("Duplicate value: " + toString(value));
        }
    }

    void displayInOrder() const {
        inorderTraversal(root);
        cout << endl;
    }

    PositiveIterator<T> positiveIterator() {
        return PositiveIterator<T>(root);
    }

    NegativeIterator<T> negativeIterator() {
        return NegativeIterator<T>(root);
    }
};

#endif 
