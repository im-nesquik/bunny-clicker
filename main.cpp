#include <Windows.h>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

constexpr const char* _0x1f1 = "\x1b[38;2;220;123;220m";
constexpr const char* _0x1f2 = "\x1b[37m";
constexpr const char* _0x1f3 = "\x1b[0m";
constexpr const char* _0x1f4 = "\x1b[32m";
constexpr const char* _0x1f5 = "\x1b[31m";

static bool _0x8d1 = false;
static float _0x8d2 = 85.0f;
static bool _0x8d3 = false;
static HHOOK _0x8d4 = nullptr;
static int _0x8d5 = 0;
static int _0x8d6 = 0;
static float _0x8d7 = 0.0f;
static float _0x9e1 = 0.0f;
static float _0x9e2 = 0.0f;

using namespace std;

static void _0x1a1(double _0x1a2) {
    static LARGE_INTEGER _0x1a3;
    static bool _0x1a4 = false;
    if (!_0x1a4) { QueryPerformanceFrequency(&_0x1a3); _0x1a4 = true; }
    LARGE_INTEGER _0x1a5, _0x1a6;
    QueryPerformanceCounter(&_0x1a5);
    double _0x1a7 = (_0x1a2 / 1000.0) * _0x1a3.QuadPart;
    do { QueryPerformanceCounter(&_0x1a6); } while ((_0x1a6.QuadPart - _0x1a5.QuadPart) < _0x1a7);
}

static float _0x2b1(int& _0x2b2) {
    static std::random_device _0x2b3;
    static std::mt19937 _0x2b4(_0x2b3());
    static float _0x2b5 = (_0x8d7 + (1000.0f / _0x9e1)) / 2.0f;
    static int _0x2b6 = 0;

    if (_0x2b6 <= 0) {
        std::uniform_real_distribution<float> _0x2b7(_0x8d7, 1000.0f / _0x9e1);
        _0x2b5 = _0x2b7(_0x2b4);
        _0x2b6 = 30 + (_0x2b3() % 50);
    }
    _0x2b6--;

    std::normal_distribution<float> _0x3c1(_0x2b5, 8.2f);
    float _0x3c2 = _0x3c1(_0x2b4);
    if ((_0x2b3() % 500) == 0) _0x3c2 += 800.0f + (_0x2b3() % 2200);
    if (_0x3c2 < _0x8d7) _0x3c2 = _0x8d7;
    if (_0x3c2 > 3333.3f) _0x3c2 = 3333.3f;

    return _0x3c2;
}

static LRESULT __stdcall _0x4d1(int _0x4d2, WPARAM _0x4d3, LPARAM _0x4d4) {
    if (_0x4d2 == HC_ACTION) {
        MSLLHOOKSTRUCT* _0x4d5 = (MSLLHOOKSTRUCT*)_0x4d4;
        if (!(_0x4d5->flags & LLMHF_INJECTED)) {
            if (_0x4d3 == WM_LBUTTONDOWN) _0x8d3 = true;
            else if (_0x4d3 == WM_LBUTTONUP) _0x8d3 = false;
        }
    }
    return CallNextHookEx(_0x8d4, _0x4d2, _0x4d3, _0x4d4);
}

static DWORD WINAPI _0x5e1(LPVOID _0x5e2) {
    _0x8d4 = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)_0x4d1, GetModuleHandle(NULL), 0);
    MSG _0x5e3;
    while (GetMessage(&_0x5e3, NULL, 0, 0)) { TranslateMessage(&_0x5e3); DispatchMessage(&_0x5e3); }
    return 0;
}

static DWORD WINAPI _0x6f1(LPVOID _0x6f2) {
    bool _0x6f3 = false;
    while (true) {
        if (GetAsyncKeyState(_0x8d5) & 0x8000) {
            if (!_0x6f3) { _0x8d1 = !_0x8d1; _0x6f3 = true; }
        }
        else _0x6f3 = false;
        _0x1a1(15);
    }
    return 0;
}

static DWORD WINAPI _0x7a1(LPVOID _0x7a2) {
    int _0x7a3 = 0;
    static std::random_device _0x7a4;
    static std::mt19937 _0x7a5(_0x7a4());
    while (true) {
        if (_0x8d3 && _0x8d1) {
            char _0x7a6[256] = { 0 };
            GetWindowTextA(GetForegroundWindow(), _0x7a6, 256);
            if (strstr(_0x7a6, "Minecraft") || FindWindowA("LWJGL", NULL)) {
                _0x8d2 = _0x2b1(_0x7a3);
                float _0x7a7 = (_0x8d2 < 85) ? 0.31f : 0.42f;
                std::uniform_real_distribution<float> _0x7a8(_0x7a7 - 0.05f, _0x7a7 + 0.05f);
                float _0x7a9 = _0x7a8(_0x7a5);
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                _0x1a1(_0x8d2 * _0x7a9);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                _0x1a1(_0x8d2 * (1.0f - _0x7a9));
                _0x7a3++;
            }
            else _0x1a1(80);
        }
        else { _0x7a3 = 0; _0x1a1(15); }
    }
    return 0;
}

static void _0x8b1() {
    HANDLE _0x8b2 = GetStdHandle(STD_OUTPUT_HANDLE);
    while (true) {
        COORD _0x8b3 = { 0, 0 };
        SetConsoleCursorPosition(_0x8b2, _0x8b3);
        printf("%sbunny lite 2.1\n\n%s", _0x1f1, _0x1f2);
        printf("status: %-15s\n", _0x8d1 ? "ON" : "OFF");
        printf("config: %.1f - %.1f CPS\n", _0x9e1, _0x9e2);;
        printf("\n\nmade by a very drunk nesquik,\ncondemed by slovak");
        Sleep(110);
        // yah! you a lil stinky but I still love ya~ <3
        // ooooo also i've kidnapped slovak he's mine GRRRR!!! >:3
    }
}

int main() {
    SetConsoleTitleA("Bunny Lite");
    printf("%sMin CPS: %s", _0x1f1, _0x1f2); scanf_s("%f", &_0x9e1);
    printf("%sMax CPS: %s", _0x1f1, _0x1f2); scanf_s("%f", &_0x9e2);
    _0x8d7 = 1000.0f / _0x9e2;

    while (GetAsyncKeyState(VK_RETURN) & 0x8000) Sleep(10);
    printf("%sSet Toggle Key... %s", _0x1f1, _0x1f2);
    while (_0x8d5 == 0) {
        for (int i = 0x02; i < 0xFE; i++) {
            if (i == VK_RETURN) continue;
            if (GetAsyncKeyState(i) & 0x8000) { _0x8d5 = i; break; }
        }
        Sleep(10);
    }

    system("cls");
    CONSOLE_CURSOR_INFO _0x8c1 = { 100, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_0x8c1);

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)_0x5e1, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)_0x7a1, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)_0x6f1, NULL, 0, NULL);

    _0x8b1();
    return 0;
}

