#include <iostream>
#include <initializer_list>
#include <string>
using namespace std;
namespace containers {

    template <typename T>
    class RList {
    public:
        struct Node {
            T value;
        private:
            Node* next;
            Node(const T& value) : value(value), next(nullptr) {}
            Node(T&& value) : value(std::move(value)), next(nullptr) {}
            friend class RList;
        };

    private:
        Node* head;
        Node* tail;
        size_t size;

        void clear() {
            while (size > 0) {
                remove(0);
            }
        }
    public:
        RList() : head(nullptr), tail(nullptr), size(0) {}
        RList(initializer_list<T> list) : RList() {
            for (const auto& item : list) {
                add(item, size);
            }
        }

        RList(const RList& other) : RList() {
            Node* current = other.head;
            for (size_t i = 0; i < other.size; ++i) {
                add(current->value, size);
                current = current->next;
            }
        }
        RList& operator=(const RList& other) {
            if (this != &other) {
                clear();
                Node* current = other.head;
                for (size_t i = 0; i < other.size; ++i) {
                    add(current->value, size);
                    current = current->next;
                }
            }
            return *this;
        }

        RList(RList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }

        RList& operator=(RList&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                tail = other.tail;
                size = other.size;
                other.head = nullptr;
                other.tail = nullptr;
                other.size = 0;
            }
            return *this;
        }

        ~RList() {
            clear();
        }

        T& operator[](size_t index) {
            if (index >= size) {
                throw out_of_range("Index out of range");
            }
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        void add(const T& value, size_t position) {
            if (position > size) {
                throw out_of_range("Position out of range");
            }

            Node* newNode = new Node(value);

            if (position == 0) {
                if (size == 0) {
                    head = tail = newNode;
                    tail->next = head; 
                }
                else {
                    newNode->next = head;
                    head = newNode;
                    tail->next = head;
                }
            }
            else {
                Node* current = head;
                for (size_t i = 0; i < position - 1; ++i) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
                if (position == size) {
                    tail = newNode;
                    tail->next = head;
                }
            }

            ++size;
        }

        void remove(size_t position) {
            if (size == 0 || position >= size) {
                throw out_of_range("Position out of range");
            }

            Node* toDelete;

            if (position == 0) {
                toDelete = head;
                head = head->next;
                tail->next = head;
                if (size == 1) {
                    head = tail = nullptr;
                }
            }
            else {
                Node* current = head;
                for (size_t i = 0; i < position - 1; ++i) {
                    current = current->next;
                }
                toDelete = current->next;
                current->next = toDelete->next;
                if (position == size - 1) {
                    tail = current;
                    tail->next = head;
                }
            }

            delete toDelete;
            --size;
        }

        size_t getSize() const {
            return size;
        }
        
        void display() const {
            Node* current = head;
            for (size_t i = 0; i < size; ++i) {
                cout << current->value << " ";
                current = current->next;
            }
            cout << endl;
        }
    };
}

int main() {
    setlocale(0, "ru");
    using namespace containers;

    RList<int> intList = { 1, 2, 3, 4, 5 };
    RList<double> doubleList = { 1.1, 2.2, 3.3 };
    RList<string> stringList = { "один", "два", "три" };

    cout << "Вывод целочисленного списка: ";
    intList.display();

    cout << "Вывод списка с плавающей точкой: ";
    doubleList.display();

    cout << "Вывод списка строк: ";
    stringList.display();

    cout << "Добавление числа 6 в intList на позицию 2:" << endl;
    intList.add(6, 2);
    intList.display();

    cout << "Удаление элемента с позиции 3 из intList:" << endl;
    intList.remove(3);
    intList.display();

    return 0;
}