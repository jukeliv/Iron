#pragma once
#include "Iron_Engine/Components/Sprite.hpp"

namespace Golden {
	class CollisionDetector
	{
	public:
		static bool bounding_sqr(const Sprite& a, const Sprite& b)
		{
			return (b.transform.position.x < a.transform.position.x + a.spr_data.w &&
				b.transform.position.x + b.spr_data.w > a.transform.position.x &&
				b.transform.position.y < a.transform.position.y + a.spr_data.h &&
				b.transform.position.y + b.spr_data.h > a.transform.position.y);
		}

		static bool bounding_circle(const Sprite& a, const Sprite& b)
		{
			return (Vec2::Distance(a.transform.position, b.transform.position) >= a.spr_data.w || Vec2::Distance(a.transform.position, b.transform.position) >= b.spr_data.w);
		}
	};
}