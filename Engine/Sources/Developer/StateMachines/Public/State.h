#pragma once
template <typename TOwner>
class StateMachine;

template <typename TOwner>
class State 
{
public:
	virtual void Initialize(TOwner* owner, StateMachine<TOwner>* machine)
	{
		_owner = owner;
		_machine = machine;
	}
	virtual void Enter() abstract;
	virtual void Exit() abstract;

protected:
	TOwner* GetOwner() { return _owner; }
	StateMachine<TOwner>* GetStateMachine() { return _machine; }

private:
	TOwner* _owner;
	StateMachine<TOwner>* _machine;
};