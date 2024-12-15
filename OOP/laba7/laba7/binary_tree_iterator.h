#ifndef BINARYTREEITERATOR_H
#define BINARYTREEITERATOR_H

#include "node.h"
#include "binary_tree_exception.h"
#include <queue>
#include <memory>
#include <stdexcept>

using namespace std;

template<typename T>
class BinaryTreeIterator {
public:
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};

template<typename T>
class PositiveIterator : public BinaryTreeIterator<T> {
private:
    queue<shared_ptr<Node<T>>> nodeQueue;

    void enqueuePositiveNodes(shared_ptr<Node<T>> node) {
        if (node) {
            if (node->value > 0) {
                nodeQueue.push(node);
            }
            enqueuePositiveNodes(node->left);
            enqueuePositiveNodes(node->right);
        }
    }

public:
    PositiveIterator(shared_ptr<Node<T>> root) {
        enqueuePositiveNodes(root);
    }

    bool hasNext() const override {
        return !nodeQueue.empty();
    }

    T next() override {
        if (nodeQueue.empty()) {
            throw BinaryTreeException("No more positive elements in the tree.");
        }

        auto currentNode = nodeQueue.front();
        nodeQueue.pop();
        return currentNode->value;
    }
};

template<typename T>
class NegativeIterator : public BinaryTreeIterator<T> {
private:
    queue<shared_ptr<Node<T>>> nodeQueue;

    void enqueueNegativeNodes(shared_ptr<Node<T>> node) {
        if (node) {
            if (node->value < 0) {
                nodeQueue.push(node);
            }
            enqueueNegativeNodes(node->left);
            enqueueNegativeNodes(node->right);
        }
    }

public:
    NegativeIterator(shared_ptr<Node<T>> root) {
        enqueueNegativeNodes(root);
    }

    bool hasNext() const override {
        return !nodeQueue.empty();
    }

    T next() override {
        if (nodeQueue.empty()) {
            throw BinaryTreeException("No more negative elements in the tree.");
        }

        auto currentNode = nodeQueue.front();
        nodeQueue.pop();
        return currentNode->value;
    }
};

#endif // BINARYTREEITERATOR_H
