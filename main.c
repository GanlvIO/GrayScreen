#include <tchar.h>
#include <windows.h>
#define SCR_W 1536
#define SCR_H 864
#define COLOR RGB(0, 0, 0)
#define ALPHA 127
#define INTERVAL 200
#define IDT_TIMER_TOPMOST 0

HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
HBRUSH hbrush; /* handle to the background brush */

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_TIMER:
		/* Set to the topmost repeatly */
		if (wParam == IDT_TIMER_TOPMOST)
			SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
		break;
	case WM_DESTROY:
		/* Upon destruction, tell the main thread to stop */
		DeleteObject(hbrush);
		KillTimer(hwnd, IDT_TIMER_TOPMOST);
		PostQuitMessage(0);
		break;
	default:
		/* All other messages (a lot of them) are processed using default procedures */
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.hbrBackground = hbrush = CreateSolidBrush(COLOR);
	wc.lpszClassName = _T("GrayWindow");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, _T("Window Registration Failed!"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW, _T("GrayWindow"), _T("GrayScreen"), WS_VISIBLE | WS_POPUP,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		SCR_W, /* width */
		SCR_H, /* height */
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, _T("Window Creation Failed!"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	SetLayeredWindowAttributes(hwnd, 0, ALPHA, LWA_ALPHA); /* Set the alpha */
	SetTimer(hwnd, IDT_TIMER_TOPMOST, INTERVAL, NULL); /* Start the timer */

	/*
	This is the heart of our program where all input is processed and
	sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
	this loop will not produce unreasonably high CPU usage
	*/
	while (GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
