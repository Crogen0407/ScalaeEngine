#include "WMMessageGETMINMAXINFO.h"
#include "BaseWindow.h"

void WMMessageGETMINMAXINFO::Enter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MINMAXINFO* pMMI = (MINMAXINFO*)lParam;

    int minSquareSize = 400;
    RECT rc = { 0, 0, minSquareSize, minSquareSize };
    DWORD style = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
    AdjustWindowRect(&rc, style, FALSE);

    pMMI->ptMinTrackSize.x = rc.right - rc.left;
    pMMI->ptMinTrackSize.y = rc.bottom - rc.top;
}