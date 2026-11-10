#pragma once
#include <string>
#include <unordered_map>

class Type
{
public:
	Type();

	static Type* GetTypeByName(const std::wstring& name)
	{
		auto it = _typeRegistry.find(name);

		if (it != _typeRegistry.end())
		{
			return it->second;
		}

		_typeRegistry[name] = new Type();
		return _typeRegistry[name];
	}

private:
	static std::unordered_map<std::wstring, Type*> _typeRegistry;
};