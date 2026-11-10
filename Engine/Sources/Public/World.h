#pragma once
#include "Object.h"
class SubSystem;

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
};