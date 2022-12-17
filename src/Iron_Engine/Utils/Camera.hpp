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

	glm::vec2 TranslatePosition(glm::vec2 in)
	{
		float x = in.x - position.x;
		float d1 = (IronGL::m_WindowConfiguration.width * getScale()) - IronGL::m_WindowConfiguration.width;
		d1 /= 2;
		x = Matloon::map(x, 0, IronGL::m_WindowConfiguration.width, -d1, IronGL::m_WindowConfiguration.width + d1);

		float y = in.y + position.y;
		float d2 = (IronGL::m_WindowConfiguration.height * getScale()) - IronGL::m_WindowConfiguration.height;
		d2 /= 2;
		y = Matloon::map(y, 0, IronGL::m_WindowConfiguration.height, -d2, IronGL::m_WindowConfiguration.height + d2);

		return { x, y };
	}
	CameraConfig m_Config;
};