#pragma once

namespace Golden
{
	//Physics functions and constants
	class Ziffy
	{
	public:
		#define G 9.81f

		inline static float cal_weight(float mass)
		{
			return mass * G;
		}

		inline static glm::vec2 cal_velocity(glm::vec2 in, float mass, const float& delta)
		{
			return in + cal_weight(mass) * in;
		}
	};
}