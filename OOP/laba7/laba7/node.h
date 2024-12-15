#ifndef NODE_H
#define NODE_H

#include <memory>
using namespace std;

template<typename T>
struct Node {
    T value;
    shared_ptr<Node<T>> left;
    shared_ptr<Node<T>> right;

    Node(const T& value) : value(value), left(nullptr), right(nullptr) {}
};

#endif 
