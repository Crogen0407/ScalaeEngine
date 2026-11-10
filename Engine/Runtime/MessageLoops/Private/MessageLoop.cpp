#include "MessageLoop.h"
#include "MessageContext.h"

MessageLoop MessageLoop::RegisterMessage(UINT messageID, MessageContext* message)
{
	_messages[messageID] = message;
	return *this;
}

bool MessageLoop::ChangeTargetMessage(HWND hWnd, UINT targetMessageID, WPARAM wParam, LPARAM lParam)
{
	if (nullptr != _currentMessage)
	{
		_currentMessage->Exit(hWnd, targetMessageID, wParam, lParam);
	}

	if (_messages.find(targetMessageID) != _messages.end())
	{
		_currentMessage = _messages[targetMessageID];
		_currentMessage->Enter(hWnd, targetMessageID, wParam, lParam);
		return true;
	}

	_currentMessage = nullptr;
	return false;
}