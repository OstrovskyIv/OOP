#ifndef BINARYTREEEXCEPTION_H
#define BINARYTREEEXCEPTION_H

#include <stdexcept>
using namespace std;

class BinaryTreeException : public runtime_error {
public:
    explicit BinaryTreeException(const string& message) : runtime_error(message) {}
};

#endif 
