#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
#include <iostream>
using namespace std;
class MemoryDump {
public:   
    static MemoryDump& getInstance() {
        static MemoryDump instance;
        return instance;
    }

private:
    MemoryDump() {
        atexit([]() {
            _CrtDumpMemoryLeaks();
            });
        cout << "MemoryDump initialized.\n";
    }

    MemoryDump(const MemoryDump&) = delete;
    MemoryDump& operator=(const MemoryDump&) = delete;

    ~MemoryDump() {
        cout << "MemoryDump destroyed.\n";
    }
};

class A {
    char* p;
public:
    A() : p(new char[1024]) {}
    ~A() { delete[] p; }
};

class B {
    char* p;
public:
    B() : p(new char[256]) {}
    ~B() { delete[] p; }
};

static A staticA;

void fn() {
    static B localStaticB;
}

int main() {
    MemoryDump& memoryDump = MemoryDump::getInstance();

    fn();

    char* testMemory = new char[128];
    delete[] testMemory;

    return 0;
}
