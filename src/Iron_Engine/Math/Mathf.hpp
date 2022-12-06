#pragma once
class Mathf
{
public:
	inline static void lerp(float& a, const double& b, const double& t)
	{
		a += (b - a) * t;
	}

	inline static void slerp(float& a, const double& b, const double& t)
	{
		double _t = 1.0f - (1.0f - t) * (1.0f - t);
		a += (b - a) * _t;
	}

	inline static void clamp(float& a, const double& min, const double& max)
	{
		a = (a < min ? a = min : (a > max ? max : a));
	}

	inline static void map(float& value,
		const float& src_min,
		const float& src_max,
		const float& dst_min,
		const float& dst_max)
	{
		value = dst_min + (dst_max - dst_min) * ((value - src_min) / (src_max - src_min));
	}
};