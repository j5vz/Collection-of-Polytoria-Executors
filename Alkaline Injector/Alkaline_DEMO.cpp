// I doubt that Alkaline would currently work, so I advise that you give me some time to figure this injection BS out and make Alkaline open-sourced for everyone.

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <vector>

void set_title(const char* title) {
    SetConsoleTitleA(title);
}

void log(const std::string& prefix, const std::string& message, WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "[";
    SetConsoleTextAttribute(hConsole, color);
    std::cout << prefix;
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << "] " << message << std::endl;
}

DWORD get_proc_id(const char* name) {
    DWORD id = 0;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(entry);
        if (Process32First(snap, &entry)) {
            do {
                if (_stricmp(entry.szExeFile, name) == 0) {
                    id = entry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snap, &entry));
        }
    }
    CloseHandle(snap);
    return id;
}

bool run_injection(DWORD pid, const char* dll_path) {
    HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!proc) return false;

    void* alloc = VirtualAllocEx(proc, nullptr, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!alloc) {
        CloseHandle(proc);
        return false;
    }

    WriteProcessMemory(proc, alloc, dll_path, strlen(dll_path) + 1, nullptr);
    HANDLE thread = CreateRemoteThread(proc, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, alloc, 0, nullptr);

    if (!thread) {
        VirtualFreeEx(proc, alloc, 0, MEM_RELEASE);
        CloseHandle(proc);
        return false;
    }

    CloseHandle(thread);
    CloseHandle(proc);
    return true;
}

int main() {
    set_title("Alkaline is now loading.");
    
    char path[MAX_PATH];
    GetFullPathNameA("module.dll", MAX_PATH, path, nullptr);

    log("[ STATUS ]", "Searching for Polytoria.exe...", 11);

    DWORD pid = 0;
    while (!pid) {
        pid = get_proc_id("Polytoria.exe");
        Sleep(500);
    }

    log("[ FOUND ]", "Target identified: " + std::to_string(pid), 10);
    log("[ INFO ]", "Injecting..", 14);

    if (run_injection(pid, path)) {
        log("[ SUCCESS ]", "Module has been attached.", 10);
    } else {
        log("[ ERROR ]", "Injection failed, check permissions.", 12);
    }

    Sleep(3000);
    return 0;
}
