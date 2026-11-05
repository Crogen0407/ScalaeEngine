#pragma once
#include "Object.h"
class SubSystem;

namespace ScalaeEngine::Core
{
	class World : public Object
	{
	public:
		World();
		virtual ~World();

	public:
		template<typename T>
		SubSystem* GetSubSystem()
		{

		}

	private:
	};
}