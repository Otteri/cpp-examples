// Server example: Create and read mailslots
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>

HANDLE hSlot;
LPCTSTR SlotName = TEXT("\\\\.\\mailslot\\example_mailslot");

BOOL ReadSlot() {
    DWORD cbMessage, cMessage, cbRead;
    BOOL fResult;
    LPTSTR lpszBuffer;
    TCHAR achID[80];
    DWORD cAllMessages;
    HANDLE hEvent;
    OVERLAPPED ov;

    cbMessage = cMessage = cbRead = 0;
    hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("ExampleSlot"));

    if (NULL == hEvent) {
        return FALSE;
    }

    ov.Offset = 0;
    ov.OffsetHigh = 0;
    ov.hEvent = hEvent;

    fResult = GetMailslotInfo(hSlot, // mailslot handle
        (LPDWORD)NULL,               // no maximum message size
        &cbMessage,                  // size of next message
        &cMessage,                   // number of messages
        (LPDWORD)NULL);              // no read time-out

    if (!fResult) {
        std::cout << "GetMailslotInfo() failed with error code:" << GetLastError() << std::endl;
        return FALSE;
    }

    if (cbMessage == MAILSLOT_NO_MESSAGE) {
        std::cout << "Waiting for a message...\n";
        return TRUE;
    }

    cAllMessages = cMessage;
    while (cMessage != 0) { // retrieve all messages

        // Create a message-number string
        StringCchPrintf((LPTSTR)achID, 80, TEXT("\nMessage #%d of %d\n"), cAllMessages - cMessage + 1, cAllMessages);

        // Allocate memory for the message
        lpszBuffer = (LPTSTR)GlobalAlloc(GPTR, lstrlen((LPTSTR)achID) * sizeof(TCHAR) + cbMessage);

        if (lpszBuffer == NULL) {
            return FALSE;
        }

        lpszBuffer[0] = '\0';
        fResult = ReadFile(hSlot, lpszBuffer, cbMessage, &cbRead, &ov);

        if (!fResult) {
            std::cout << "ReadFile() failed with error code: " << GetLastError() << std::endl;
            GlobalFree((HGLOBAL)lpszBuffer);
            return FALSE;
        }

        // Concatenate the message and the message-number string
        StringCbCat(lpszBuffer, lstrlen((LPTSTR)achID) * sizeof(TCHAR) + cbMessage, (LPTSTR)achID);

        // Display the message
        _tprintf(TEXT("Contents of the mailslot: %s\n"), lpszBuffer);

        GlobalFree((HGLOBAL)lpszBuffer);
        fResult = GetMailslotInfo(hSlot,  // mailslot handle
            (LPDWORD)NULL,                // no maximum message size
            &cbMessage,                   // size of next message
            &cMessage,                    // number of messages
            (LPDWORD)NULL);               // no read time-out


        if (!fResult) {
            std::cout << "GetMailslotInfo() failed with error code: " << GetLastError() << std::endl;
            return FALSE;
        }
    }

    if (CloseHandle(hEvent) == 0) {
        printf("Fail to close hEvent handle, error %d\n", GetLastError());
    }

    return TRUE;
}


BOOL WINAPI MakeSlot(LPCTSTR lpszSlotName) {
    hSlot = CreateMailslot(lpszSlotName,
        0,                             // no maximum message size
        MAILSLOT_WAIT_FOREVER,         // no time-out for operations
        (LPSECURITY_ATTRIBUTES)NULL);  // default security

    if (hSlot == INVALID_HANDLE_VALUE) {
        std::cout << "CreateMailslot() failed with error code: " << GetLastError() << std::endl;
        return FALSE;
    }
    std::cout << "Created a Mailslot" << std::endl;
    return TRUE;
}


int main(int argc, char** argv) {
    MakeSlot(SlotName);

    while (TRUE) {
        ReadSlot();
        Sleep(2000);
    }

    return 0;
}

