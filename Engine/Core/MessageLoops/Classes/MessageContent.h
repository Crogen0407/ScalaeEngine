#pragma once

namespace ScalaeEngine::Core::MessageLoops
{
	class MessageContent
	{
		MessageContent(UINT targetMessage);
		virtual ~MessageContent() = 0;

	public:
		virtual bool PeckedMessage() = 0;

	private:
		UINT _targetMessage;
	};
}
