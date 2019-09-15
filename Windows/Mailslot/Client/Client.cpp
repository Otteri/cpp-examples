// Creating and writing mailslot example
#include <windows.h>
#include <stdio.h>
#include <iostream>

LPCTSTR SlotName = TEXT("\\\\.\\mailslot\\example_mailslot");

BOOL WriteSlot(HANDLE hSlot, LPCTSTR lpszMessage) {
    BOOL fResult;
    DWORD cbWritten;

    fResult = WriteFile(hSlot, lpszMessage, (DWORD)(lstrlen(lpszMessage) + 1) * sizeof(TCHAR), &cbWritten, (LPOVERLAPPED)NULL);

    if (!fResult) {
        std::cout << "WriteFile() failed with error code:" << GetLastError() << std::endl;
        return FALSE;
    }
    else {
        std::cout << "Wrote a message to mailslot" << std::endl;
    }

    return TRUE;
}



int main(int argc, char** argv) {
    HANDLE hFile;

    // Open handle to the mailslot
    hFile = CreateFile(SlotName, GENERIC_WRITE, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "CreateFile() failed with error code: " << GetLastError() << std::endl;
        return FALSE;
    }

    // Send messages
    WriteSlot(hFile, TEXT("First message"));
    WriteSlot(hFile, TEXT("Second message"));
    Sleep(3000);
    WriteSlot(hFile, TEXT("Third messge"));


    if (CloseHandle(hFile) == 0) {
        std::cout << "Fail to close hFile handle, error:" << GetLastError() << std::endl;
    }

    return TRUE;
}