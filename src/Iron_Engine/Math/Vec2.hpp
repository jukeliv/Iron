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

	static double Distance(Vec2 a, Vec2 b)
	{
		return std::sqrtf((b.x * a.x) + (b.y * a.y));
	}

	static double DistanceSqr(Vec2 a, Vec2 b)
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