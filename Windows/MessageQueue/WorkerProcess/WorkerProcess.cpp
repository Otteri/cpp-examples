#include <iostream>
#include "Windows.h"

int main(int argc, char* argv[]) {
    MSG message;
    while (true) {
        std::cout << "[Child] Working until requested to stop..." << std::endl;
        if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)) {
            std::cout << "[Child] Recieved a message: " << message.message << std::endl;
            break;
        }
        Sleep(1000);
    }
    std::cout << "[Child] Terminating..." << std::endl;
    return 0;
}
