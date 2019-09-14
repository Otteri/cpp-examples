#include "ExplicitLoad.h"
#include "ImplicitLinking.h"

// This project demonstrates different ways to create and load a DLL.
// Use "BinaryDumpTool.py" script to inspect the created DLL.
// This shows how the function names may get automatically mangled.


// The DLL-functions are automatically imported, so we can call
// them immediately. Fast & easy! The downside of this method is 
// that the linker cannot proceed without .lib and header file,
// so in order to create this .exe, we must provide those two!
int ImplicitLoadExample() {
    printHello();
    return 0;
}

// The functions must be load from the DLL 'manually' and this
// requires some code, which is separated into another file.
// The extra work can be worth it, if the DLL must be load on
// runtime or we need full control of the interface declarations.
int ExplicitLoadExample() {
    loadExplicitly();
    return 0;
}

int main() {
    ImplicitLoadExample();
    ExplicitLoadExample();
    return 0;
}

