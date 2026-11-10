#pragma once
#include "MessageContext.h"

class WMMessageDestroy : public MessageContext
{
public:
	void Enter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};