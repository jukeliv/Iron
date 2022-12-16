#pragma once

#include <Iron_Engine/Engine.hpp>
#include <Iron_Engine/Golden/RigidBody.hpp>

class Mascot : GameObject
{
public:
	Mascot()
		:sprite(transform,"res/images/slime.png"), 
		collider(Transform(),Golden::ColliderType::SquareCollider),
		rigidBody(transform)
	{
		animator = std::make_unique<Animator>(sprite);
		this->transform.scale = glm::vec2(4);
		sprite.ScreenCenter();

		sprite.transform.position.x = 0;

		animator->AddByRects("idle", { {0, 0, 21, 21}, {0, 21, 21, 21}, {21, 0, 21, 21}, {0, 21, 21, 21} }, 3);

		animator->PlayAnim("idle");
	}

	void Update(Input& input, const Time& time)
	{
		rigidBody.acceleration.y = (input.keys[SDLK_q] ? -1 : 1);

		animator->step(time);
		rigidBody.step(time);
		collider.step(sprite.transform.position, glm::vec2(24));
	}

	void Render(Camera& camera)
	{
		sprite.Render(camera);
	}

	~Mascot()
	{
		animator.release();
		delete animator.get();
	}

public:
	std::unique_ptr<Animator> animator;
	RigidBody rigidBody;
	Sprite sprite;

	Golden::Collider collider;
};