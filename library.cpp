#include <windows.h>
#include <tuple>

std::tuple<int, int> screenToAbsolute(int x, int y) {
    // multi monitor support
    int offsetTop = abs(GetSystemMetrics(SM_YVIRTUALSCREEN));
    int offsetLeft = abs(GetSystemMetrics(SM_XVIRTUALSCREEN));
    int screenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    x += offsetLeft;
    y += offsetTop;
    int absX = (x * 65535) / (screenWidth - 1);
    int absY = (y * 65535) / (screenHeight - 1);
    return {absX, absY};
}

extern "C" {
[[maybe_unused]] __declspec(dllexport) void __cdecl moveMouse(int, int);
}

[[maybe_unused]] extern void __cdecl moveMouse(int x, int y) {
    auto[absX, absY] = screenToAbsolute(x, y);

    // Move mouse
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = absX;
    input.mi.dy = absY;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;
    ::SendInput(1, &input, sizeof(INPUT));
    ::ZeroMemory(&input, sizeof(INPUT));
}

extern "C" {
[[maybe_unused]] __declspec(dllexport) void __cdecl clickPos(bool, int, int);
}

[[maybe_unused]] extern void __cdecl clickPos(bool left, int x, int y) {
    auto[absX, absY] = screenToAbsolute(x, y);

    // Move mouse
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = absX;
    input.mi.dy = absY;
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
[[maybe_unused]] __declspec(dllexport) void __cdecl click(bool);
}

[[maybe_unused]] extern void __cdecl click(bool left) {
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