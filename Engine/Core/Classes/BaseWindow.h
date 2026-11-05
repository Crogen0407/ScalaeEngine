#pragma once

namespace ScalaeEngine::Core
{
    class Engine;

    class BaseWindow
    {
    public:
        BaseWindow();

		bool Initialize(HWND hWnd);
        int Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
		void CleanUp();

    public:
        void CreateWindowHandle();
        ATOM RegisterWindowClassEx();
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
		HINSTANCE _hInstance;
        HWND	  _hWnd;
		Engine*   _engine;
    };
}
