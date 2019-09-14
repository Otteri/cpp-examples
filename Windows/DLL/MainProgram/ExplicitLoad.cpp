#include "windows.h"
#include <iostream>

// function pointer typedefs:
typedef double(*fnptr_Convert_inch2cm)(double);
fnptr_Convert_inch2cm Convert_inch2cm;

int releaseDll(HMODULE hDll) {
    std::cout << "Failed to load the Dll function\n";
    FreeLibrary(hDll);
    return 1;
}

int loadDll(HMODULE hDll) {
    hDll = LoadLibrary(TEXT("Library.dll"));
    if (!hDll) {
        std::cout << "Couldn't load the DLL." << std::endl;
        std::cout << "Are all the dependencies included and is the Dll path correct?" << std::endl;
        return -1;
    }

    // Load the functions defined in the DLL.
    // Since we used extern "C" when exporting, the function name is exactly same as in the source.
    // Without the extern "C" it can be tricky to know the function name as the names may get mangled.
    // This is one reason why the interface should be pure C, so we can use the extern "C" keyword.
    Convert_inch2cm = (fnptr_Convert_inch2cm)GetProcAddress(hDll, "Convert_inch2cm");
    if (!Convert_inch2cm) {
        releaseDll(hDll);
        std::cout << "Unable to load a function from the DLL." << std::endl;
        return -1;
    }

    return 1;
}

int loadExplicitly() {
    HMODULE hDll = nullptr;

    loadDll(hDll);

    // Use the function loaded from the DLL:
    std::cout << "5.0 inches is " << Convert_inch2cm(5.0) << " cm\n";

    return 0;
}

