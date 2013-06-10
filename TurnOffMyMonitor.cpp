/**
 * Turn Off My Monitor v1.0 by Espen 'Rexxars' Hovlandsdal - www.rexxars.com
 * Turns off your monitors and lets you specify a time to wait before doing so.
 *
 * Compile with something similar to:
 *
 *    cl /O2 /MD TurnOffMyMonitor.cpp  /FeTurnOffMyMonitor.exe /link 
 *        /subsystem:windows /defaultlib:user32.lib /defaultlib:shell32.lib
 *
 * If you are not running this from the Visual Studio Command Line, then you
 * might have to add include paths and library paths in the command line
 */

// We want to be using the Unicode variants
#define UNICODE

#include <windows.h>
// For CommandLineToArvW()
#include <shellapi.h>
// For _wtoi()
#include <wchar.h>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR lpCmdLine, int) {
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(lpCmdLine, &argc);

    if (argv == NULL) {
        MessageBox(NULL, L"CommandLineToArgvW() failed.", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return 0;
    }

    // Initalize variables
    int sleepTime;
    
    // Check if the user has specified a sleep time
    if (argc > 0) {
        sleepTime = _wtoi(argv[0]);
    }
    
    // If the user hasn't specified a sleep time, or has inserted some jibberish,
    // default the sleep time to 500 milliseconds
    if (argc != 1 || sleepTime == 0) {
        // Give some feedback concerning sleep times and the proper usage
        LPWSTR message = 
            L"Usage: TurnOffMyMonitor.exe <milliseconds>\n"
            L"Where <milliseconds> specifies the number of milliseconds to wait before turning off your monitor(s).\n"
            L"Values between 1 and 2147483647 are accepted, default is 500.";

        MessageBox(NULL, message, L"Info", MB_OK | MB_ICONINFORMATION);
        sleepTime = 500;
    }

    // Now sleep for the specified time
    Sleep(sleepTime);

    // And turn off the monitor!
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);

    // Die, gracefully.
    return 0;
}
