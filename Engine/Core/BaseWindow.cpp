#include "Classes/BaseWindow.h"
#include "Classes/Engine.h"

namespace ScalaeEngine::Core
{
    BaseWindow::BaseWindow()
    {
		_engine = new Engine();
    }

    bool BaseWindow::Initialize(HWND hWnd)
    {
        return false;
    }

    int BaseWindow::Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
    {
		_hInstance = hInstance;
		if (NULL == _hInstance)
		{
			cout << "Failed to get instance handle" << endl;
			return -1;
		}
        RegisterWindowClassEx();
        CreateWindowHandle();
        ::ShowWindow(_hWnd, nCmdShow);
        ::SetWindowPos(_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        ::UpdateWindow(_hWnd); // WM_PAINT

		while (true)
		{
			MSG msg;
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
                _engine->GameLoop();
			}
		}

        return 0;
    }

    void BaseWindow::CleanUp()
    {
    }

    void BaseWindow::CreateWindowHandle()
    {
        int ResolutionX = GetSystemMetrics(SM_CXSCREEN);
        int ResolutionY = GetSystemMetrics(SM_CYSCREEN);

        int Winposx = ResolutionX / 2 - SCREEN_WIDTH / 2;
        int Winposy = ResolutionY / 2 - SCREEN_HEIGHT / 2;

        _hWnd = ::CreateWindow(
            L"Test",
            L"Test",
            WS_OVERLAPPEDWINDOW, 
            Winposx,
            Winposy, 
            SCREEN_WIDTH, 
            SCREEN_HEIGHT,
            nullptr,
            nullptr,
            _hInstance,
            nullptr);

		if (NULL == _hWnd)
		{
            DWORD errCode = GetLastError();
            cout << "Failed to register window class. Error code: " << errCode << endl;
            return;
		}
        RECT rt = { Winposx , Winposy, Winposx + SCREEN_WIDTH, Winposy + SCREEN_HEIGHT };
        ::AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
        ::MoveWindow(_hWnd, Winposx, Winposy, rt.right - rt.left, rt.bottom - rt.top, false);
    }

    ATOM BaseWindow::RegisterWindowClassEx()
    {
        WNDCLASSEXW wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = BaseWindow::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = _hInstance;
        wcex.hIcon = nullptr;
        //wcex.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON1));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = L"Test";
        wcex.hIconSm = nullptr;
        //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
		auto atom = ::RegisterClassEx(&wcex);
        if (NULL == atom)
        {
            DWORD errCode = GetLastError();
			cout << "Failed to register window class. Error code: " << errCode << endl;
        }

        return atom;
    }

    LRESULT BaseWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_GETMINMAXINFO:
        {
            MINMAXINFO* pMMI = (MINMAXINFO*)lParam;

            int minSquareSize = 400;

            RECT rc = { 0, 0, minSquareSize, minSquareSize };
            DWORD style = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
            AdjustWindowRect(&rc, style, FALSE);

            pMMI->ptMinTrackSize.x = rc.right - rc.left;
            pMMI->ptMinTrackSize.y = rc.bottom - rc.top;

            return 0;
        }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }
}