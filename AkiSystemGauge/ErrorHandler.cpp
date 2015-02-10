#include <string>

#include "ErrorHandler.hpp"

// A simple error handler that shows a message box with the provided message.
// Also allows for a GET_SYSTEM_ERROR flag to append a GetLastError() message to the error message.
void HandleErrorMsg( 
              const char* errorMessage, 
              const char* errorCaption, 
              ERROR_FLAG errorFlag,
              HWND hwnd
              )
{
    std::string errorStr = "Application error message:\r\n";

    errorStr.append(errorMessage);

    if (errorFlag == GET_SYSTEM_ERROR)
    {
        DWORD dw = GetLastError();
        char* lpMsgBuf = NULL;

        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&lpMsgBuf),
            0, 
            NULL
            );

        if (lpMsgBuf != NULL)
        {
            errorStr.append("\r\nSystem error message:\r\n");
            errorStr.append(static_cast<char*>(lpMsgBuf));
        }
    }

    MessageBoxA(hwnd, errorStr.c_str(), errorCaption, MB_OK);
}