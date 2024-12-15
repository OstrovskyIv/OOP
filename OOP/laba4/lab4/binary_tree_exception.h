#ifndef BINARYTREEEXCEPTION
#define BINARYTREEEXCEPTION

#include <stdexcept>
using namespace std;

class BinaryTreeException : public runtime_error {
public:
    explicit BinaryTreeException(const string& message) : runtime_error(message) {}
};

#endif 
