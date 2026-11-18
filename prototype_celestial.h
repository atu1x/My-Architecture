#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <dwmapi.h>
#ifdef _MSC_VER
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#endif

#include <vector>
#include <cstdint>
#include <algorithm>
#include <atomic>

namespace celestial {
	struct celvec2 { float x = 0.f, y = 0.f; };
	struct celvec3 { float x = 0.f, y = 0.f, z = 0.f; };
	struct celvec4 { float x = 0.f, y = 0.f, z = 0.f, w = 0.f; };

	inline std::atomic<bool> running{ false };
	inline void stop() { running = false; }

	inline LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
		if (message == WM_DESTROY) {
			running = false;
			return 0;
		}
		return DefWindowProcW(hwnd, message, wparam, lparam);
	}

	inline void setupAndRender() {
		if (running) return;

		// setup
		SetProcessDPIAware();

		int canvas_width = GetSystemMetrics(SM_CXSCREEN);
		int canvas_height = GetSystemMetrics(SM_CYSCREEN);
		std::vector<uint32_t> pixels(canvas_width * canvas_height, 0);

		WNDCLASSW wc = {};
		wc.lpfnWndProc = window_proc;
		wc.hInstance = GetModuleHandleW(nullptr);
		wc.lpszClassName = L"celestial_overlay";
		RegisterClassW(&wc);

		HWND hwnd = CreateWindowExW(
			WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
			wc.lpszClassName, L"Celestial", WS_POPUP,
			0, 0, canvas_width, canvas_height,
			nullptr, nullptr, wc.hInstance, nullptr
		);
		if (!hwnd) return;

		SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
		MARGINS margins = { -1, -1, -1, -1 };
		DwmExtendFrameIntoClientArea(hwnd, &margins);
		ShowWindow(hwnd, SW_SHOWNOACTIVATE);

		BITMAPINFO bmi = {};
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = canvas_width;
		bmi.bmiHeader.biHeight = -canvas_height;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;

		HDC hdc = GetDC(hwnd);
		running = true;

		// present
		while (running) {
			// premise (win message)
			MSG msg = {};
			while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}

			// clear/initialization (std fill solos ngl)
			std::fill(pixels.begin(), pixels.end(), 0x00000000);

			// stupid rect filler
			celvec4 rect = { 100.f, 100.f, 500.f, 350.f };
			uint32_t color = 0xFFFF0000;

			int start_x = std::clamp(static_cast<int>(rect.x), 0, canvas_width);
			int start_y = std::clamp(static_cast<int>(rect.y), 0, canvas_height);
			int end_x = std::clamp(static_cast<int>(rect.z), 0, canvas_width);
			int end_y = std::clamp(static_cast<int>(rect.w), 0, canvas_height);

			if (start_x < end_x) {
				for (int y = start_y; y < end_y; ++y) {
					uint32_t* row = pixels.data() + y * canvas_width;
					std::fill(row + start_x, row + end_x, color);
				}
			}

			//vsync & reflection
			StretchDIBits(hdc, 0, 0, canvas_width, canvas_height, 0, 0, canvas_width, canvas_height, pixels.data(), &bmi, DIB_RGB_COLORS, SRCCOPY);
			DwmFlush();
		}

		// shutdown bruh 3 lines
		ReleaseDC(hwnd, hdc);
		DestroyWindow(hwnd);
		UnregisterClassW(wc.lpszClassName, wc.hInstance);
	}
}
