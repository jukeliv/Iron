#pragma once
#include <glm/glm.hpp>
#include <Iron_Engine/Components/Sprite.hpp>

namespace Golden
{
	enum class ColliderType { CircleCollider, SquareCollider };

	class Collider
	{
	public:
		Collider(const Transform& _bounds, ColliderType _ct)
			:bounds(_bounds), ct(_ct) {}
		Collider(ColliderType _ct)
			:bounds(), ct(_ct) {}

		bool CheckColliding(const Collider& other)
		{
			if (ct != other.ct)
				ERROR("GOLDEN CAN'T MANAGE MULTIPLE COLLIDER TYPES");

			//Axis-Aligned Bounding Boxes
			if (ct == ColliderType::SquareCollider) {
				//TODO: Center the collision so it is not on the corner of the sprite
				return (other.bounds.position.x < bounds.position.x + bounds.scale.x &&
					other.bounds.position.x + other.bounds.scale.x > bounds.position.x &&
					other.bounds.position.y < bounds.position.y + bounds.scale.y &&
					other.bounds.position.y + other.bounds.scale.y > bounds.position.y);
			}
			//Circle Collision Detection
			if (ct == ColliderType::CircleCollider)
				return (glm::distance(bounds.position, other.bounds.position) < (bounds.scale.r + other.bounds.scale.r));

			return false;
		}

		inline void step(const Sprite& _spr)
		{
			bounds.position = _spr.transform.position;
			bounds.scale = _spr.data.bounds * _spr.transform.scale;
		}

		inline void step(const glm::vec2& _position, const glm::vec2& _scale)
		{
			bounds.position = _position;
			bounds.scale = _scale;
		}
	public:
		//Variables
		Transform bounds;
		ColliderType ct;
	};
}