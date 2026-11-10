#pragma once
#include "../MessageLoops/Public/MessageLoop.h"

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

public:
    const HWND* GetHWND() { return &_hWnd; }

private:
	HINSTANCE _hInstance;
    HWND	  _hWnd;
	Engine*   _engine;
    static MessageLoop _messageLoop;
};