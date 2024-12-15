#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

void prepareInputFile(const string& filename) {
    ofstream inputFile(filename);
    if (!inputFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 100; ++i) {
        int randomNumber = rand() % 101 - 50; 
        inputFile << randomNumber << endl;
    }

    inputFile.close();
}

int findFirstOdd(const vector<int>& numbers) {
    for (int num : numbers) {
        if (abs(num) % 2 == 1) {
            return num;
        }
    }
    return 0; 
}

void processFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);

    if (!inputFile || !outputFile) {
        cerr << "Ошибка открытия файлов!" << endl;
        return;
    }

    vector<int> numbers;
    int num;

    while (inputFile >> num) {
        numbers.push_back(num);
    }

    inputFile.close();

    int firstOdd = findFirstOdd(numbers);

    for (int num : numbers) {
        outputFile << num + firstOdd << endl;
    }

    outputFile.close();
}

int main() {
    setlocale(0, "ru");
    cout << setw(10) << "t" << setw(10) << "cos(t)" << endl;
    cout << fixed << setprecision(3);
    for (double t = 0; t <= 3; t += 0.5) {
        cout << setw(10) << t << setw(10) << cos(t) << endl;
    }

    string inputFilename = "input.txt";
    string outputFilename = "output.txt";

    prepareInputFile(inputFilename);
    processFile(inputFilename, outputFilename);

    cout << "Обработка файлов завершена. Результаты записаны в " << outputFilename << endl;

    return 0;
}
