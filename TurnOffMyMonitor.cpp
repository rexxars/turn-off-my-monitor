/**
 * Turn Off My Monitor v1.0 by Espen 'Rexxars' Hovlandsdal - www.rexxars.com
 * Turns off your monitors and lets you specify a time to wait before doing so.
 */

#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Initalize variables
    int sleepTime;

    // Give some feedback.
    printf("\n");
    printf("Turn Off My Monitor v1.0 by Espen 'Rexxars' Hovlandsdal - www.rexxars.com\n");
    printf("Turns off your monitor(s) and lets you specify a time to wait before doing so.\n\n");

    // Check if the user has specified a sleep time
    if (argc > 1) {
        sleepTime = atoi(argv[1]);
    }
    
    // If the user hasn't specified a sleep time, or has inserted some jibberish,
    // default the sleep time to 500 milliseconds
    if (argc == 1 || sleepTime == 0) {
        // Give some feedback concerning sleep times and the proper usage
        printf("Usage: TurnOffMyMonitor.exe <milliseconds>\n");
        printf("Where <milliseconds> specifies the number of milliseconds to wait before\n");
        printf("turning off your monitor(s). Values between 1 and 2147483647 are accepted.\n\n");
        sleepTime = 500;
    }

    // Give some feedback on the sleep time
    printf("Going to wait %d milliseconds before I put your monitor(s) to sleep.\n", sleepTime);

    // Now sleep for the specified time
    Sleep(sleepTime);

    // And turn off the monitor!
    printf("Putting your monitor(s) to sleep now.\n");
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);

    // Die, gracefully.
    return 0;
}
