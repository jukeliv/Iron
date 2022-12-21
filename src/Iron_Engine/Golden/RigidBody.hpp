#pragma once

#include <Iron_Engine/Engine.hpp>

namespace Golden::Ziffy
{
	typedef struct RigidBodyConfiguration
	{
		float mass = 1;
		float velocity = 0.5f;
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
				force.x -= force.x > 0 ? time.delta : -time.delta;

			if (force.y != 0)
				force.y -= force.y > 0 ? time.delta : -time.delta;

			glm::vec2 acc = ZiffyFunc::cal_force(acceleration, config.mass);
			force += acc;
			if (force.length() < acc.length())
				force += glm::vec2(force.x - acc.x * config.velocity, force.y - acc.y * config.velocity);
			else if (force.length() > acc.length())
				force -= glm::vec2(force.x - acc.x * config.velocity, force.y - acc.y * config.velocity);


			transform.position += force * time.delta;
		}

	public:
		glm::vec2 force;
		glm::vec2 acceleration;
		RigidBodyConfiguration config;
		Transform& transform;
	};
}