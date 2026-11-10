#include "WMMessageDestroy.h"

void WMMessageDestroy::Enter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
}