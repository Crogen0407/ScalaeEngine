#pragma once
#include <map>
#include "State.h"

template <typename TOwner>
class StateMachine
{
public:
	StateMachine* Append(UINT id, State<TOwner>* state)
	{
		_states[id] = state;
		return this;
	}
	void Initialize(TOwner* owner)
	{
		_owner = owner;
		_currentState = _states.begin()->second;
	}

public:
	void ChangeState(UINT id)
	{
		if (_currentState != nullptr)
			_currentState->Exit();

		auto it = _states.find(id);
		if (it != _states.end())
		{
			_currentState = it->second;
			_currentState->Enter();
		}
		else
		{
			std::cout << "State with ID " << id << " not found." << std::endl;
			_currentState = nullptr;
		}
	}

public:
	const State<TOwner>* GetCurrentState() { return _currentState; }
	const TOwner* GetOwner() { return _owner; }

private:
	TOwner* _owner = nullptr;
	std::map<UINT, State<TOwner>*> _states;
	State<TOwner>* _currentState = nullptr;
};