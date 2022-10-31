#pragma once
#include <unordered_map>
#include <string_view>

class Entity
{
public:
	Entity()
	{

	}

	virtual ~Entity()
	{

	}

	virtual void Update() {}

	virtual void Render() {}
};