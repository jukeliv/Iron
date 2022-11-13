#pragma once

struct Collider
{
	Collider(const Vec2& b)
		:bounds(b), position(0,0){}
	//Dont use transform, for now we dont need rotation :/
	Vec2 position;

	Vec2 bounds;
};

namespace Golden {
	class CollisionDetector
	{
	public:
		static bool bounding_sqr(const Collider& a, const Collider& b)
		{
			return (b.position.x < a.position.x + a.bounds.x &&
				b.position.x + b.bounds.x > a.position.x &&
				b.position.y < a.position.y + a.bounds.y &&
				b.position.y + b.bounds.y > a.position.y);
		}

		/*
		* dont use this, is broken xd
		static bool bounding_circle(const Sprite& a, const Sprite& b)
		{
			return (Vec2::Distance(a.transform.position, b.transform.position) >= a.spr_data.w || Vec2::Distance(a.transform.position, b.transform.position) >= b.spr_data.w);
		}*/
	};
}