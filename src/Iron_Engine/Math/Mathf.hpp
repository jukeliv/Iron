#pragma once
class Mathf
{
public:
	static void lerp(double& a, const double& b, const double& t)
	{
		a += (b - a) * t;
	}

	static void clamp(double& a, const double& min, const double& max)
	{
		if (a < min)
			a = min;
		else if (a > max)
			a = max;
	}

	static void map(float& value,
		const float& src_min,
		const float& src_max,
		const float& dst_min,
		const float& dst_max)
	{
		value = dst_min + (dst_max - dst_min) * ((value - src_min) / (src_max - src_min));
	}
};