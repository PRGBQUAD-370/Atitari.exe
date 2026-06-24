#include <Windows.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <time.h>
#include <ctime>
#include <string>
#include <stdio.h>
#include <limits.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE r;
        BYTE g;
        BYTE b;
        BYTE Reserved;
    };
}_RGBQUAD, * PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) {
    if (red != length) {
        red < length; red++;
        if (ifblue == true) {
            return RGB(red, 0, length);
        }
        else {
            return RGB(red, 0, 0);
        }
    }
    else {
        if (green != length) {
            green < length; green++;
            return RGB(length, green, 0);
        }
        else {
            if (blue != length) {
                blue < length; blue++;
                return RGB(0, length, blue);
            }
            else {
                red = 0; green = 0; blue = 0;
                ifblue = true;
            }
        }
    }
}
bool running = true;
COLORREF HSV(int h) {
    h %= 360;
    int x = (255 * (60 - abs((h % 120) - 60))) / 60;
    switch (h / 60) {
    case 0:  return RGB(255, x, 0);
    case 1:  return RGB(x, 255, 0);
    case 2:  return RGB(0, 255, x);
    case 3:  return RGB(0, x, 255);
    case 4:  return RGB(x, 0, 255);
    default: return RGB(255, 0, x);
    }
}
DWORD WINAPI train(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, -60, 0, w, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, w - 60, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}
DWORD WINAPI squares(LPVOID lpParam) {
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    int x = 100, y = 100;
    int dx = 14, dy = 12;
    const int size = 110;
    while (running) {
        HDC hdc = GetDC(0);
        HBRUSH brush = CreateSolidBrush(HSV(240));
        HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
        SelectObject(hdc, brush);
        SelectObject(hdc, pen);
        Rectangle(hdc, x, y, x + size, y + size);
        DeleteObject(brush);
        DeleteObject(pen);
        ReleaseDC(0, hdc);
        x += dx;
        y += dy;
        if (x <= 0 || x + size >= screenW) dx = -dx;
        if (y <= 0 || y + size >= screenH) dy = -dy;

        Sleep(8);
    }
    return 0;
}
DWORD WINAPI masher(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(HWND_DESKTOP);
        int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
        BitBlt(hdc, rand() % 5, rand() % 5, rand() % sw, rand() % sh, hdc, rand() % 5, rand() % 5, SRCCOPY);
        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI MoveScreenInvert(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (true)
    {
        hdc = GetDC(0);
        BitBlt(hdc, 0, -5, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, 0, h - 5, w, h, hdc, 0, 0, NOTSRCCOPY);
        BitBlt(hdc, -5, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, w - 5, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        ReleaseDC(GetDesktopWindow(), hdc);
        DeleteDC(hdc);
    }
}
DWORD WINAPI TextOut1(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int sx = GetSystemMetrics(0);
    int sy = GetSystemMetrics(1);
    LPCWSTR lpText = L"Atitari.exe";
    while (true)
    {
        hdc = GetDC(0);
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
        ReleaseDC(GetDesktopWindow(), hdc);
        DeleteDC(hdc);
        Sleep(10);
    }
}
DWORD WINAPI CursorText(LPVOID lpvd) {
    HDC hdc = GetDC(0);
    POINT cursorPt;
    int sx = GetCursorPos(&cursorPt);
    int sy = GetCursorPos(&cursorPt);
    LPCWSTR lpText = L"Hi I'm following ur cursor";
    while (true)
    {
        hdc = GetDC(0);
        GetCursorPos(&cursorPt);
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, cursorPt.x, cursorPt.y, lpText, wcslen(lpText));
        ReleaseDC(GetDesktopWindow(), hdc);
        DeleteDC(hdc);
        Sleep(10);
    }
}
DWORD WINAPI sharpen(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(0);
        int sw = GetSystemMetrics(0);
        int sh = GetSystemMetrics(1);
        SetStretchBltMode(hdc, 4);
        StretchBlt(hdc, 1, 1, sw + 2, sh + 2, hdc, 0, 0, sw, sh, SRCCOPY);
        StretchBlt(hdc, -1, -1, sw - 2, sh - 2, hdc, 0, 0, sw, sh, SRCCOPY);
        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI textout1(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int signX1 = 1;
    int signY1 = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    LPCSTR lpText = "Hax";
    while (1) {
        HDC hdc = GetDC(0);
        x += incrementor * signX;
        y += incrementor * signY;
        int top_x = 0 + x;
        int top_y = 0 + y;
        SetBkMode(hdc, 0);
        SetTextColor(hdc, Hue(239));
        //SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFontA(43, 32, 0, 0, FW_THIN, 0, 1, 0, ANSI_CHARSET, 0, 0, 0, 0, "Baby Kruffy");
        SelectObject(hdc, font);
        TextOutA(hdc, top_x, top_y, lpText, strlen(lpText));
        if (y >= GetSystemMetrics(SM_CYSCREEN))
        {
            signY = -1;
        }

        if (x >= GetSystemMetrics(SM_CXSCREEN))
        {
            signX = -1;
        }

        if (y == 0)
        {
            signY = 1;
        }

        if (x == 0)
        {
            signX = 1;
        }
        Sleep(4);
        DeleteObject(font);
        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI hslfill(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(NULL);
        int x = GetSystemMetrics(SM_CXSCREEN),
            y = GetSystemMetrics(SM_CYSCREEN);

        HBRUSH brush = CreateSolidBrush(Hue(239));
        SelectObject(hdc, brush);
        BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, PATCOPY);
        DeleteObject(brush);
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}
DWORD WINAPI Final(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN),
			h = GetSystemMetrics(SM_CYSCREEN);
		StretchBlt(hdc, 10, 10, w - 20, h - 20, hdc, 0, 0, w, h, SRCINVERT);
		StretchBlt(hdc, -10, -10, w + 20, h + 20, hdc, 0, 0, w, h, SRCINVERT);
		ReleaseDC(NULL, hdc);
	}
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((((t / 2 * (4 | t >> 13 & 3) >> (~t >> 11 & 1) | ~t >> 5) & 127) + (t * (t >> 11 & t >> 13) * (~t >> 9 & 3) & 127) / 2 + ((t & 4096 ? (t * (t ^ t % 255) | t >> 5) >> 1 : t >> 4 | (t & 8192 ? t << 1 : t)) & 127) + 64));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (42 & t >> 10));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((15 * t & t >> 4 | 5 * t & t >> 7 | 3 * t & t >> 10) - 1);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((t & 4096 ? t % 65536 < 59392 ? 7 : t & 7 : 16) + (1 & t >> 16)) >> (3 & t >> (t & 2048 ? 2 : 10)) | t >> (t & 16384 ? t & 4096 ? 4 : 3 : 2));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 6 & t >> 2));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[16000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(10 * (t >> 7 | 3 * t | t >> (t >> 15)) + (t >> 8 & 5));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    if (MessageBoxA(0, "Atitari.exe, Run GDI?", "Atitari.exe", MB_YESNO | MB_ICONWARNING) == IDNO) {
        return 0;
    }
    if (MessageBoxA(0, "Are you sure you want to run it?", "Atitari.exe", MB_YESNO | MB_ICONWARNING) == IDNO) {
        return 0;
    }

    Sleep(1000);
    HANDLE F1 = CreateThread(0, 0, train, 0, 0, 0);
    sound1();
    Sleep(30000);
    TerminateThread(F1, 0);
    CloseHandle(F1);
    Sleep(1000);
    HANDLE F2 = CreateThread(0, 0, masher, 0, 0, 0);
    HANDLE F2Z1 = CreateThread(0, 0, squares, 0, 0, 0);
    sound2();
    Sleep(30000);
    TerminateThread(F2, 0);
    CloseHandle(F2);
    TerminateThread(F2Z1, 0);
    CloseHandle(F2Z1);
    Sleep(1000);
    HANDLE F3 = CreateThread(0, 0, MoveScreenInvert, 0, 0, 0);
    sound3();
    Sleep(30000);
    TerminateThread(F3, 0);
    CloseHandle(F3);
    Sleep(1000);
    HANDLE F4 = CreateThread(0, 0, TextOut1, 0, 0, 0);
    HANDLE F4Z1 = CreateThread(0, 0, CursorText, 0, 0, 0);
    sound4();
    Sleep(30000);
    TerminateThread(F4, 0);
    CloseHandle(F4);
    TerminateThread(F4Z1, 0);
    CloseHandle(F4Z1);
    Sleep(1000);
    HANDLE F5 = CreateThread(0, 0, sharpen, 0, 0, 0);
    PlaySoundW(L"sound5.wav", NULL, SND_FILENAME | SND_ASYNC);
    Sleep(30000);
    TerminateThread(F5, 0);
    CloseHandle(F5);
    Sleep(1000);
    HANDLE F6 = CreateThread(0, 0, textout1, 0, 0, 0);
    sound6();
    Sleep(30000);
    TerminateThread(F6, 0);
    CloseHandle(F6);
    Sleep(1000);
    HANDLE F7 = CreateThread(0, 0, hslfill, 0, 0, 0);
    sound7();
    Sleep(30000);
    TerminateThread(F7, 0);
    CloseHandle(F7);
    Sleep(1000);
    HANDLE F8 = CreateThread(0, 0, Final, 0, 0, 0);
    PlaySoundW(L"sound8.wav", NULL, SND_FILENAME | SND_ASYNC);
    Sleep(30000);
}