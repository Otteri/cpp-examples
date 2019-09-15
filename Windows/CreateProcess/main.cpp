#include "CreateProcess.h"
#include "DuplicateProcess.h"
#include <iostream>

// Demonstrates how a existing process can be duplicated
// and how a new process can be created.

int main(int argc, TCHAR* argv[]) {

    std::cout << "[Duplicate process]" << std::endl;
    duplicateProcessExample(argc, argv);

    std::cout << "[Create process]" << std::endl;
    createProcess(argc, argv);
    
    std::cout << "Done!" << std::endl;

    return 0;
}