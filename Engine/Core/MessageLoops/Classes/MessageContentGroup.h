#pragma once
class MessageContent;

namespace ScalaeEngine::Core::MessageLoops
{
	class MessageContentGroup
	{
		MessageContentGroup();

	private:
		template<typename T>
		void AddMessageContent(UINT targetMessage)
		{
			auto messageContent = new T(targetMessage);
			_messageContents.push_back(messageContent);
		}

	private:
		std::vector<MessageContent*> _messageContents;
	};
}
