#pragma once

namespace Golden::Ziffy
{
	//Physics functions and constants
	class ZiffyFunc
	{
	public:
		#define G 9.81f

		inline static float cal_weight(float mass)
		{
			return mass * G;
		}

		inline static glm::vec2 cal_force(glm::vec2 acc, float mass)
		{
			//F = M*A
			return mass * acc;
		}
	};
}