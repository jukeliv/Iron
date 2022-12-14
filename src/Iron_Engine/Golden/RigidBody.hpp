#pragma once

#include <Iron_Engine/Engine.hpp>

typedef struct RigidBodyConfiguration
{
	float mass = 5;
	bool kinematic = false;
}RigidBodyConfiguration;

class RigidBody
{
public:
	RigidBody(Transform& _transform)
		:transform(_transform), force({ 0 }), velocity({ 0 }) {}

	void step(const Time& time)
	{
		if (force.x != 0)
			force.x -= force.x>0?time.delta:-time.delta;

		if (force.y != 0)
			force.y -= force.y > 0 ? time.delta : -time.delta;
		
		if(!config.kinematic)
			velocity += Golden::Ziffy::cal_velocity(force, config.mass, time.delta);

		transform.position += velocity;
	}

public:
	glm::vec2 force;
	glm::vec2 velocity;
	RigidBodyConfiguration config;
	Transform& transform;
};