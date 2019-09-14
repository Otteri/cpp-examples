#include <iostream>
#include "Windows.h"

// Short description:
// This main process spawns a worker process. Worker process
// runs until it is asked to stop. Main program requests worker
// to stop by sending a messages via message queue.


// Path to the sub-process executable.
std::string path = "Output/WorkerProcess.exe";

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    std::cout << "[Main] Trying to create a child process" << std::endl;
    std::wstring exe_path = std::wstring(path.begin(), path.end());
    LPCWSTR swPath = exe_path.c_str();
    CreateProcess(swPath, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

    Sleep(6000);       // Let the worker process to run a while
    
    PostThreadMessage( // Send a message
        pi.dwThreadId, // Thread id
        999,           // Message type
        0,             // Additional message info
        0              // Even more message info
    );

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    std::cout << "[Main] Terminating..." << std::endl;
    return 0;
}
