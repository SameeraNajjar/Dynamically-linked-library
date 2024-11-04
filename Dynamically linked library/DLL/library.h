#pragma once

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

extern "C" {
    DLL_EXPORT void sort(int* a, const int size);
    DLL_EXPORT void readInfo(int* a, const int size);
    DLL_EXPORT void display(int* a, const int size);
    DLL_EXPORT int computeAvg(int* a, const int size);
}

