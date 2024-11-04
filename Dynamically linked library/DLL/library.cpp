#include "pch.h"
#include "library.h"
#include <iostream>
using namespace std;
extern "C" {
    __declspec(dllexport) void sort(int* a, const int size) {
        // Implementation of sorting algorithm 
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (a[j] > a[j + 1]) {
                    int temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }
    }

    __declspec(dllexport) void readInfo(int* a, const int size) {
        // Implementation of reading input into the array
        for (int i = 0; i < size; ++i) {
            cin >> a[i];
        }
    }

    __declspec(dllexport) void display(int* a, const int size) {
        // Implementation of displaying the array elements
        cout << "array elements: ";
        for (int i = 0; i < size; i++)
        {
            cout << a[i] << " \n";
        }
    }
    
    __declspec(dllexport) int computeAvg(int* a, const int size) {
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += a[i];
        }
        return sum / size;
    }
}
