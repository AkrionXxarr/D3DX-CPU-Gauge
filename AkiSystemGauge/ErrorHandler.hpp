#ifndef _ERROR_HANDLER_HPP_
#define _ERROR_HANDLER_HPP_

#include <windows.h>

enum ERROR_FLAG { DEFAULT_ERROR, GET_SYSTEM_ERROR };

void HandleErrorMsg( 
              const char* errorMessage, 
              const char* errorCaption, 
              ERROR_FLAG errorFlag,
              HWND hwnd
              );

/*
class ErrorHandler
{
    ErrorHandler(const char* errorMsg, bool getLastError);
};
*/

#endif