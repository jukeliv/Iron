#pragma once

class Entity
{
public:
	Entity()
	{

	}

	virtual ~Entity()
	{

	}

	virtual void Update(const double& delta) {}

	virtual void Render() {}
};