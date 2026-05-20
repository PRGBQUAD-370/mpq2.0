#include <Windows.h>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <iostream>
#pragma comment(lib, "winmm.lib")
#define M_PI   3.14159265358979323846264338327950288
#define _USE_MATH_DEFINES 1
//typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
//typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, *PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
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
DWORD WINAPI payload0(LPVOID lpParam) {
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		desktop = GetDC(NULL);
		BitBlt(desktop, 1, 1, xs, ys, desktop, -2, 2, SRCERASE);
		ReleaseDC(0, desktop);
		Sleep(10);
	}
}
DWORD WINAPI payload1(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (true)
	{
		hdc = GetDC(0);
		BitBlt(hdc, 1, 1, w, h, hdc, 0, 0, SRCINVERT);
		BitBlt(hdc, -1, -1, w, h, hdc, 0, 0, SRCINVERT);
		ReleaseDC(GetDesktopWindow(), hdc);
		DeleteDC(hdc);
		Sleep(10);
	}

}
DWORD WINAPI payload2(LPVOID lpParam) {
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		desktop = GetDC(NULL);
		BitBlt(desktop, 0, 0, xs, ys, desktop, -1, -1, SRCERASE);
		ReleaseDC(0, desktop);
		Sleep(10);
	}
}
DWORD WINAPI payload3(LPVOID lpParam)
{
	while (1) {
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN),
			h = GetSystemMetrics(SM_CYSCREEN);
		StretchBlt(hdc, 10, 10, w - 20, h - 20, hdc, 0, 0, w, h, SRCINVERT);
		StretchBlt(hdc, -10, -10, w + 20, h + 20, hdc, 0, 0, w, h, SRCINVERT);
		ReleaseDC(NULL, hdc);
	}
}
DWORD WINAPI TextOut(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sx = GetSystemMetrics(0);
	int sy = GetSystemMetrics(1);
	LPCWSTR lpText = L"mpq.exe";
	while (true)
	{
		hdc = GetDC(0);
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
		ReleaseDC(GetDesktopWindow(), hdc);
		DeleteDC(hdc);
	}
}
DWORD WINAPI RGB1(LPVOID lpParam)
{
	while (1) {
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN),
			h = GetSystemMetrics(SM_CYSCREEN);

		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shader1(LPVOID lpParam) {
	HDC hdc = GetDC(0); HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double angle = 0;
	while (1) {
		hdc = GetDC(0);
		for (float i = 0; i < sw + sh; i += 1.99f) {
			int a = sin(angle) * 700;
			BitBlt(hdc, 0, i, sw, 1, hdc, a, i, SRCCOPY);
			angle += M_PI / 3;
			DeleteObject(&i); DeleteObject(&a);
		}
		ReleaseDC(wnd, hdc);
		DeleteDC(hdc); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&angle);
	}
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((9 * t & t >> 4 | 5 * t & t >> 7 | 3 * t & t >> 10) - 0);

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
        buffer[t] = static_cast<char>(t << 1 ^ (t << 1) + (t >> 7) & t >> 12 | t >> 4 - (1 ^ 7 & t >> 19) | t >> 7);

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
        buffer[t] = static_cast<char>(t * ((t & 4096 ? t % 65536 < 59392 ? 7 : t & 7 : 16) + (1 & t >> 14)) >> (3 & -t >> (t & 2048 ? 2 : 10)) | t >> (t & 16384 ? t & 4096 ? 10 : 3 : 2));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
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

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	if (MessageBoxW(NULL, L"mpq2.0.exe, Run?", L"mpq2.0.exe by prgbquad-370", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure it contains Heavy GDI", L"mpq2.0.exe-Final Warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else

			Sleep(1000);
			HANDLE P1 = CreateThread(NULL, 0, payload0, NULL, 0, NULL);
			PlaySoundW(L"sound1.wav", NULL, SND_FILENAME | SND_ASYNC);
			Sleep(60000);
			TerminateThread(P1, 0);
			CloseHandle(P1);
			Sleep(100);
			HANDLE P2 = CreateThread(NULL, 0, payload1, NULL, 0, NULL);
			Sleep(60000);
			TerminateThread(P2, 0);
			CloseHandle(P2);
			HANDLE P3 = CreateThread(NULL, 0, payload2, NULL, 0, NULL);
			Sleep(60000);
			TerminateThread(P3, 0);
			CloseHandle(P3);
			Sleep(100);
			HANDLE P4 = CreateThread(NULL, 0, payload3, NULL, 0, NULL);
			sound2();
			Sleep(30000);
			TerminateThread(P4, 0);
			CloseHandle(P4);
			Sleep(100);
			HANDLE P5 = CreateThread(NULL, 0, TextOut, NULL, 0, NULL);
			sound3();
			Sleep(30000);
			TerminateThread(P5, 0);
			CloseHandle(P5);
			Sleep(100);
			HANDLE P6 = CreateThread(NULL, 0, RGB1, NULL, 0, NULL);
			sound4();
			Sleep(30000);
			TerminateThread(P6, 0);
			CloseHandle(P6);
			Sleep(100);
			HANDLE P7 = CreateThread(NULL, 0, shader1, NULL, 0, NULL);
			sound5();
			Sleep(30000);
			TerminateThread(P7, 0);
			CloseHandle(P7);
			Sleep(100);

	}
}