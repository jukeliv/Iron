#pragma once

#include <Iron_Engine/Engine.hpp>

typedef struct RigidBodyConfiguration
{
	float mass = 1;
	float velocity = 0;
	bool kinematic = false;
}RigidBodyConfiguration;

class RigidBody
{
public:
	RigidBody(Transform& _transform)
		:transform(_transform), force({ 0 }), acceleration({ 0 }) {}

	void step(const Time& time)
	{
		if (force.x != 0)
			force.x -= force.x>0?time.delta:-time.delta;

		if (force.y != 0)
			force.y -= force.y > 0 ? time.delta : -time.delta;
		
		force += Golden::Ziffy::cal_force(acceleration, config.mass);

		transform.position += (force * time.delta);
	}

public:
	glm::vec2 force;
	glm::vec2 acceleration;
	RigidBodyConfiguration config;
	Transform& transform;
};