#include "duplicateProcess.h"
#include <iostream>

int duplicateProcess(int argc, TCHAR* argv[]) {

    static LPCWSTR szProcessMutex = TEXT("TesterProcess");
    static HANDLE hHandle = CreateMutex(NULL, TRUE, szProcessMutex);

    if (ERROR_ALREADY_EXISTS == GetLastError()) {
        // Avoid recursion - we want to create only one child process
        std::cout << "Mutex handle already exists: skip child process creation\n";
        return -1;
    }

    // Create a new process
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    CreateProcess(argv[0], NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

    // Master continues from here, but the child starts from the beginning
    std::cout << "  Created a child process successfully\n";

    ::WaitForSingleObject(pi.hProcess, INFINITE); // Master waits child to exit
    
    // Upon child closing:
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    ReleaseMutex(hHandle); // Explicitly release mutex
    CloseHandle(hHandle);  // close the handle before terminating
    std::cout << "  Closed the child process" << std::endl;

    return 1;
}


int duplicateProcessExample(int argc, TCHAR* argv[])
{
    auto startTime = std::chrono::steady_clock::now();
    duplicateProcess(argc, argv);
    auto endTime = std::chrono::steady_clock::now();

    std::cout << "  Duplication time: " <<
        std::chrono::duration <double, std::milli>(endTime - startTime).count()
        << " ms" << std::endl;

    return 0;
}

