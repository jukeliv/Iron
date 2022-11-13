#pragma once
#include <stdlib.h>

struct Vec2
{
public:
	float x, y;

	Vec2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	Vec2 operator+=(const Vec2& o) {
		x += o.x;
		y += o.y;
		return *this;
	}

	Vec2 operator-=(const Vec2& o) {
		x -= o.x;
		y -= o.y;
		return *this;
	}

	Vec2 operator*=(const float& o) {
		x *= o;
		y *= o;
		return *this;
	}

	Vec2 operator/=(const float& o) {
		x /= o;
		y /= o;
		return *this;
	}

	Vec2 operator*(const float& o) {
		return {x*o, y*o};
	}

	static float Distance(const Vec2& a, const Vec2& b)
	{
		return std::sqrtf((b.x * a.x) + (b.y * a.y));
	}
	
	static float DistanceSqr(const Vec2& a, const Vec2& b)
	{
		return (b.x * a.x) + (b.y * a.y);
	}

	void normalize()
	{
		Vec2 in = { this->x, this->y };
		this->operator/=(Distance(in, in));
		this->operator*=(10);
	}
};