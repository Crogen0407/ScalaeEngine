#pragma once
#include "MessageContext.h"

class WMMessageGETMINMAXINFO : public MessageContext
{
public:
	void Enter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};