#pragma once
#include <glm/glm.hpp>
#include <Iron_Engine/Components/Sprite.hpp>

enum class ColliderType {CircleCollider, SquareCollider};

typedef struct Collider
{
	Collider(const Transform& _bounds, ColliderType _ct)
		:bounds(_bounds), ct(_ct) {}
	Transform bounds;	

	ColliderType ct;
} Collider;

namespace Golden {
	class CollisionDetector
	{
	public:

		static bool DetectCollision(const Collider& a, const Collider& b)
		{
			//Axis-Aligned Bounding Boxes
			if (a.ct == ColliderType::SquareCollider && b.ct == ColliderType::SquareCollider) {
				return (b.bounds.position.x < a.bounds.position.x + a.bounds.scale.x &&
					b.bounds.position.x + b.bounds.scale.x > a.bounds.position.x &&
					b.bounds.position.y < a.bounds.position.y + a.bounds.scale.y &&
					b.bounds.position.y + b.bounds.scale.y > a.bounds.position.y);
			}
			//Circle Collision Detection
			if (a.ct == ColliderType::CircleCollider && b.ct == ColliderType::CircleCollider)
			{
				return (glm::distance(a.bounds.position, b.bounds.position) < (a.bounds.scale.r + b.bounds.scale.r));
			}
		}
	};
}