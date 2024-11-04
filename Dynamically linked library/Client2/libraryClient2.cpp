#include <iostream>
#include <windows.h>

using namespace std;

typedef void (*sort_func_t)(int*, const int);
typedef void (*readInfo_func_t)(int*, const int);
typedef void (*display_func_t)(int*, const int);
typedef int (*computeAvg_func_t)(int*, const int);

int main() {
    // Ask the user to provide the DLL path or name
    string dllPath;
    cout << "Enter the name of the DLL : ";
    cin >> dllPath;

    // Load the DLL dynamically at runtime
    HINSTANCE hLib = LoadLibraryA(dllPath.c_str());
    if (!hLib) {
        cerr << "Error loading library: " << GetLastError() << endl;
        return 1;
    }

    // Resolve function addresses dynamically
    sort_func_t sort_func = (sort_func_t)GetProcAddress(hLib, "sort");
    readInfo_func_t readInfo_func = (readInfo_func_t)GetProcAddress(hLib, "readInfo");
    display_func_t display_func = (display_func_t)GetProcAddress(hLib, "display");
    computeAvg_func_t computeAvg_func = (computeAvg_func_t)GetProcAddress(hLib, "computeAvg");

    if (!sort_func || !readInfo_func || !display_func || !computeAvg_func) {
        cerr << "Error finding functions: " << GetLastError() << endl;
        FreeLibrary(hLib);
        return 1;
    }

    // Get the size of the array from the user
    int size;
    cout << "Enter the number of integers: ";
    cin >> size;

    // Dynamically allocate the array
    int* arr = new int[size];

    // Read array elements from the user
    cout << "Enter " << size << " integers: ";
    readInfo_func(arr, size);

    // Ask the user what operations they want to perform
    char option;
    cout << "Do you want to sort the array? (y/n): ";
    cin >> option;
    if (option == 'y' || option == 'Y') {
        sort_func(arr, size);
    }

    cout << "Do you want to display the array? (y/n): ";
    cin >> option;
    if (option == 'y' || option == 'Y') {
        display_func(arr, size);
    }

    cout << "Do you want to compute the average of the array? (y/n): ";
    cin >> option;
    if (option == 'y' || option == 'Y') {
        int avg = computeAvg_func(arr, size);
        cout << "Average: " << avg << endl;
    }

    // Clean up and free resources
    delete[] arr;
    FreeLibrary(hLib);
    return 0;
}
