#pragma once

namespace Golden
{
	//Physics functions and constants
	class Ziffy
	{
	public:
		#define GRAVITY 9.81f

		inline static float cal_mass(float weight)
		{
			return weight * GRAVITY;
		}

		inline static glm::vec2 cal_velocity(glm::vec2 in, float weight, const float& delta)
		{
			return in * cal_mass(weight) * delta;
		}
	};
}