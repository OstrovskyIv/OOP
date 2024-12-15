#include <iostream>
#include <initializer_list>
#include <string>
#include <stdexcept>

using namespace std;

namespace containers {

    template <typename T>
    class NameClass {
    public:
        struct Node {
            T value;                
        private:
            Node* next;             
            explicit Node(const T& val) : value(val), next(nullptr) {}
            explicit Node(T&& val) : value(std::move(val)), next(nullptr) {}
            friend class NameClass<T>;
        };

        NameClass() : head(nullptr), tail(nullptr), size(0) {}

        NameClass(initializer_list<T> init) : NameClass() {
            for (const T& val : init) {
                push_back(val);
            }
        }

        NameClass(const NameClass& other) : NameClass() {
            Node* current = other.head;
            while (current) {
                push_back(current->value);
                current = current->next;
            }
        }

        NameClass(NameClass&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
            other.head = other.tail = nullptr;
            other.size = 0;
        }

        NameClass& operator=(const NameClass& other) {
            if (this != &other) {
                clear();
                Node* current = other.head;
                while (current) {
                    push_back(current->value);
                    current = current->next;
                }
            }
            return *this;
        }

        NameClass& operator=(NameClass&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                tail = other.tail;
                size = other.size;
                other.head = other.tail = nullptr;
                other.size = 0;
            }
            return *this;
        }

        ~NameClass() {
            clear();
        }

        T& operator[](size_t index) {
            if (index >= size) throw underflow_error("Индекс вне диапазона");
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        void push_back(const T& value) {
            Node* newNode = new Node(value);
            if (!tail) {
                head = tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
            ++size;
        }

        void pop_back() {
            if (!tail) throw underflow_error("Контейнер пуст");
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            }
            else {
                Node* current = head;
                while (current->next != tail) {
                    current = current->next;
                }
                delete tail;
                tail = current;
                tail->next = nullptr;
            }
            --size;
        }

        size_t get_size() const {
            return size;
        }

        void clear() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            tail = nullptr;
            size = 0;
        }

    private:
        Node* head; 
        Node* tail; 
        size_t size; 
    };

    template <typename T>
    class RList {
    public:
        struct Node {
            T value;
            Node* next;
            explicit Node(const T& val) : value(val), next(nullptr) {}
            explicit Node(T&& val) : value(std::move(val)), next(nullptr) {}
        };

        RList() : head(nullptr), tail(nullptr) {}

        ~RList() {
            clear();
        }

        void push_back(const T& value) {
            Node* newNode = new Node(value);
            if (!tail) {
                head = tail = newNode;
                tail->next = head; 
            }
            else {
                tail->next = newNode;
                tail = newNode;
                tail->next = head; 
            }
        }

        void pop_front() {
            if (!head) throw underflow_error("Контейнер пуст");
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            }
            else {
                Node* temp = head;
                head = head->next;
                tail->next = head; 
                delete temp;
            }
        }

        void display() const {
            if (!head) {
                cout << "Список пуст\n";
                return;
            }
            Node* current = head;
            do {
                cout << current->value << " ";
                current = current->next;
            } while (current != head);
            cout << "\n";
        }

        void clear() {
            if (!head) return;
            tail->next = nullptr; 
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            tail = nullptr;
        }

    private:
        Node* head;
        Node* tail;
    };

} 

int main() {
    setlocale(0, "ru");
    using namespace containers; 

    NameClass<int> intContainer{ 1, 2, 3, 4 };
    intContainer.push_back(5);
    cout << "intContainer: ";
    for (size_t i = 0; i < intContainer.get_size(); ++i) {
        cout << intContainer[i] << " ";
    }
    cout << "\n";

    RList<string> stringList;
    stringList.push_back("Один");
    stringList.push_back("Два");
    stringList.push_back("Три");
    cout << "RList: ";
    stringList.display();
    stringList.pop_front();
    cout << "После pop_front: ";
    stringList.display();

    return 0;
}
