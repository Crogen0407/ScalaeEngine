#pragma once
#include <unordered_map>

class MessageContext;
class MessageLoop
{
public:
	MessageLoop RegisterMessage(UINT messageID, MessageContext* message);
	bool ChangeTargetMessage(HWND hWnd, UINT targetMessageID, WPARAM wParam, LPARAM lParam);

private:
	MessageContext* _currentMessage = nullptr;
	std::unordered_map<UINT, MessageContext*> _messages;
};