// Credits:
// https://guidedhacking.com/
// https://learn.microsoft.com/en-us/search/

#include <iostream>

#include "proc.h"
#include "mem.h"



int main()
{
    // Variables:
    bool bOptionOne = false;
    bool bOptionTwo = false;
    DWORD procId = 0;
    HANDLE hProcess = nullptr;
    uintptr_t moduleBase = 0;
    uintptr_t dynamicPtrBaseAddr = 0;

    // Attempt to get process ID and module base address
    procId = GetProcId(L"name.exe");
    if (procId == 0)
    {
        std::cerr << "Failed to retrieve process ID." << std::endl;
        return 1;
    }

    moduleBase = GetModuleBaseAddress(procId, L"name.exe");
    if (moduleBase == 0)
    {
        std::cerr << "Failed to retrieve module base address." << std::endl;
        return 1;
    }

    // Open the process with appropriate access rights
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    if (hProcess == nullptr)
    {
        std::cerr << "Failed to open process. Error: " << GetLastError() << std::endl;
        return 1;
    }

    dynamicPtrBaseAddr = moduleBase + 0x000000;

    // Main loop to monitor process and handle options
    DWORD dwExit = 0;
    while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE)
    {
        // Toggle option one with VK_NUMPAD1
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bOptionOne = !bOptionOne;
            // Execute option one logic here if needed
        }

        // Toggle option two with VK_NUMPAD2
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bOptionTwo = !bOptionTwo;
            // Execute option two logic here if needed
        }

        // Execute option two logic every tick if bOptionTwo is true
        if (bOptionTwo)
        {
            // Execute logic for option two every tick
        }

        Sleep(10); // Adjust the sleep duration as needed
    }

    // Close the process handle before exiting
    CloseHandle(hProcess);
    return 0;
}
