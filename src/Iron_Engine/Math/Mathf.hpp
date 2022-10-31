#pragma once
class Mathf
{
public:
	static void lerp(double& a, const double& b, const double& t)
	{
		a += (b - a) * t;
	}
};