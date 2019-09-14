#pragma once
#include <Windows.h>

int loadExplicitly();
int loadDll(HMODULE hDll);
int releaseDll(HMODULE hDll);