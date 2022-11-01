#pragma once

#include <iostream>
struct Vec2
{
public:
	double x, y;

	Vec2(double x, double y)
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

	static double Distance(const Vec2& a, const Vec2& b)
	{
		return std::sqrtf((b.x * a.x) + (b.y * a.y));
	}
	
	static double DistanceSqr(const Vec2& a, const Vec2& b)
	{
		return (b.x * a.x) + (b.y * a.y);
	}

	static Vec2 normalized(const Vec2& in)
	{
		Vec2 out = in;
		double l = Distance(in, in);

		out.x /= l;
		out.y /= l;

		out.x *= 10;
		out.y *= 10;

		return out;
	}
};