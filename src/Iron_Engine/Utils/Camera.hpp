#pragma once

#include <glm\glm.hpp>
#include <Iron_Engine/Math/Matloon.hpp>
typedef struct CameraConfig
{
public:
	float fov = 120;//this is default fov, no one can dissagree this
}CameraConfig;

class Camera
{
public:
	Camera()
		:position({ 0,0 })
	{}
	~Camera() {}
public:
	glm::vec2 position;
	//this is only used for the sprite class, never touch this
	float getScale()
	{
		float val = Matloon::map(m_Config.fov, 120, 160, 160, 120) / 120 - .333333f;//simple fix to round this to 1.0f instead of 1.3333333333333333333f
		return val;
	}
	CameraConfig m_Config;
};