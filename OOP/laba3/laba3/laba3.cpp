#include <iostream>
#include <string>
using namespace std;

template <typename T>
class APtrArr {
private:
    T* ptr; 
    size_t size; 

public:
    APtrArr() : ptr(nullptr), size(0) {}

    APtrArr(size_t n) : ptr(new T[n]{}), size(n) {}

    APtrArr(const APtrArr&) = delete;

    APtrArr& operator=(const APtrArr&) = delete;

    APtrArr(APtrArr&& other) noexcept : ptr(other.ptr), size(other.size) {
        other.ptr = nullptr;
        other.size = 0;
    }

    APtrArr& operator=(APtrArr&& other) noexcept {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            size = other.size;
            other.ptr = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~APtrArr() {
        delete[] ptr;
    }

    void reset() {
        delete[] ptr;
        ptr = nullptr;
        size = 0;
    }

    void swap(APtrArr& other) {
        APtrArr<T>* temp = ptr;
        ptr = other.ptr;
        other.ptr = temp;
        size_t tempSize = size;
        size = other.size;
        other.size = tempSize;
    }

    T* get() const {
        return ptr;
    }

    size_t getSize() const {
        return size;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return ptr[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return ptr[index];
    }
};

int main() {
    setlocale(0, "ru");
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Работа с массивом int\n";
        cout << "2. Работа с массивом double\n";
        cout << "3. Работа с массивом string\n";
        cout << "4. Выход\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            size_t size;
            cout << "Введите размер массива int: ";
            cin >> size;
            APtrArr<int> intArr(size);
            for (size_t i = 0; i < size; ++i) {
                intArr[i] = static_cast<int>(i * 10);
            }
            cout << "Элементы массива int: ";
            for (size_t i = 0; i < size; ++i) {
                cout << intArr[i] << " ";
            }
            cout << "\n";
            break;
        }
        case 2: {
            size_t size;
            cout << "Введите размер массива double: ";
            cin >> size;
            APtrArr<double> doubleArr(size);
            for (size_t i = 0; i < size; ++i) {
                doubleArr[i] = i * 0.1;
            }
            cout << "Элементы массива double: ";
            for (size_t i = 0; i < size; ++i) {
                cout << doubleArr[i] << " ";
            }
            cout << "\n";
            break;
        }
        case 3: {
            size_t size;
            cout << "Введите размер массива string: ";
            cin >> size;
            APtrArr<string> stringArr(size);
            for (size_t i = 0; i < size; ++i) {
                cout << "Введите строку для элемента " << i << ": ";
                cin >> stringArr[i];
            }
            cout << "Элементы массива string: ";
            for (size_t i = 0; i < size; ++i) {
                cout << stringArr[i] << " ";
            }
            cout << "\n";
            break;
        }
        case 4:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 4);

    return 0;
}
