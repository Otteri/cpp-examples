#pragma once
#include <Windows.h>
#include <chrono>

int duplicateProcessExample(int argc, TCHAR* argv[]);

void printExecutionTime(std::chrono::time_point<std::chrono::steady_clock>,
    std::chrono::time_point<std::chrono::steady_clock>);
