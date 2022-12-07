#pragma once
//Matloon ( Math library ) by JukeLiv
namespace Matloon {
	inline static float avrg(const float arr[])
	{
		float temp = 0;
		size_t i = 0;
		while (i < sizeof(arr))
		{
			temp += arr[i];
			i++;
		}

		return temp / sizeof(arr);
	}

	inline static float lerp(const float& a, const float& b, const float& t)
	{
		return a + (b - a) * t;
	}

	inline static float slerp(const float& a, const float& b, const float& t)
	{
		float _t = 1.0f - (1.0f - t) * (1.0f - t);
		return a + (b - a) * _t;
	}

	inline static float clamp(const float& a, const double& min, const double& max)
	{
		return (a < min ? min : (a > max ? max : a));
	}

	inline static float map
	(const float& value,
		const float& src_min,
		const float& src_max,
		const float& dst_min,
		const float& dst_max)
	{
		return dst_min + (dst_max - dst_min) * ((value - src_min) / (src_max - src_min));
	}
}