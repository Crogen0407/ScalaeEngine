#pragma once

class MessageContext
{
public:
	virtual void Enter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) abstract;
	virtual void Exit(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { /* Empty */ }
};