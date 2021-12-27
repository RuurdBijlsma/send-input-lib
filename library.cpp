#include <windows.h>
#include <chrono>

void sendKeyPress(bool down, int key) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.time = 0;
    if (down) {
        input.ki.dwFlags = KEYEVENTF_SCANCODE;
    } else {
        input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    }
    input.ki.wScan = MapVirtualKey(key, MAPVK_VK_TO_VSC);
    input.ki.wVk = 0;

    input.ki.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));
}

extern "C" {
__declspec(dllexport) void __cdecl sendKey(bool, int);
}

// https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// ENTER: 13
// ESCAPE: 27
// SPACE: 32
// LEFT: 37
// UP: 38
// RIGHT: 39
// DOWN: 40
// DELETE: 46
extern void __cdecl sendKey(bool down, int key) {
    sendKeyPress(down, key);
}


extern "C" {
__declspec(dllexport) void __cdecl clickPos(bool, int, int);
}

extern void __cdecl clickPos(bool left, int x, int y) {
    int screenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    // Move mouse
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = (x * 65535) / (screenWidth - 1);
    input.mi.dy = (y * 65535) / (screenHeight - 1);
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;
    ::SendInput(1, &input, sizeof(INPUT));
    ::ZeroMemory(&input, sizeof(INPUT));

    // Down
    input.type = INPUT_MOUSE;
    if (left) {
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    } else {
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    }
    ::SendInput(1, &input, sizeof(INPUT));

    // Up
    ::ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    if (left) {
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    } else {
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    }
    ::SendInput(1, &input, sizeof(INPUT));
}

extern "C" {
__declspec(dllexport) void __cdecl click(bool);
}

extern void __cdecl click(bool left) {
    INPUT input = {0};
    // down
    input.type = INPUT_MOUSE;
    if (left) {
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    } else {
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    }
    ::SendInput(1, &input, sizeof(INPUT));

    // up
    ::ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    if (left) {
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    } else {
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    }
    ::SendInput(1, &input, sizeof(INPUT));
}