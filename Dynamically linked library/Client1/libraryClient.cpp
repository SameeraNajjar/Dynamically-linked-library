#include <iostream>
#include <windows.h>

using namespace std;

typedef void (*sort_func_t)(int*, const int);
typedef void (*readInfo_func_t)(int*, const int);
typedef void (*display_func_t)(int*, const int);
typedef int (*computeAvg_func_t)(int*, const int);

int main() {
    string dllName;

    // Ask user to enter the DLL name
    cout << "Enter the name of the DLL: ";
    cin >> dllName;

    // Load the DLL
    HINSTANCE hLib = LoadLibraryA(dllName.c_str());

    if (!hLib) {
        cerr << "Error opening shared library: " << GetLastError() << endl;
        return 1;
    }

    // Resolve symbols
    sort_func_t sort_func = (sort_func_t)GetProcAddress(hLib, "sort");
    readInfo_func_t readInfo_func = (readInfo_func_t)GetProcAddress(hLib, "readInfo");
    display_func_t display_func = (display_func_t)GetProcAddress(hLib, "display");
    computeAvg_func_t computeAvg_func = (computeAvg_func_t)GetProcAddress(hLib, "computeAvg");

    if (!sort_func || !readInfo_func || !display_func || !computeAvg_func) {
        cerr << "Error finding symbols: " << GetLastError() << endl;
        FreeLibrary(hLib);
        return 1;
    }

    const int size = 5;
    int arr[size];

    // Read array elements
    cout << "Enter " << size << " integers: ";
    readInfo_func(arr, size);

    // Display the array elements before sorting
    cout << "Before sorting:" << endl;
    display_func(arr, size);

    // Sort the array
    sort_func(arr, size);

    // Display the array elements after sorting
    cout << "After sorting:" << endl;
    display_func(arr, size);

    // Compute and display the average
    int avg = computeAvg_func(arr, size);
    cout << "Average of the array elements: " << avg << endl;

    // Free the library after usage
    FreeLibrary(hLib);

    return 0;
}
