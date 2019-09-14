#pragma once

// 1) Export C++ code -- (names will be possibly mangled)
#define DLL_EXPORT __declspec(dllexport)

class DLL_EXPORT Convert {
public:
    static double inch2cm(int inches);
    static double inch2cm(double inches);
};


// 2) Export C code (name mangling doesn't happen)
// This is simply a wrapper function for the previous class
extern "C" __declspec(dllexport)
double Convert_inch2cm(double inches);