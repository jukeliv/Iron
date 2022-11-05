#pragma once
#include <stdlib.h>

struct Vec2
{
public:
	float x, y;

	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void AddVector(const Vec2& other)
	{
		this->x = this->x + other.x; this->y = this->y + other.y;
	}

	void SubVector(const Vec2& other)
	{
		this->x = this->x - other.x; this->y = this->y - other.y;
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
		double l = Distance(in, in);

		this->x /= l;
		this->y /= l;

		this->x *= 10;
		this->y *= 10;
	}
};