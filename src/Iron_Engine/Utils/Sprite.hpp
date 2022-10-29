#pragma once

#include "Iron_Engine\Core.hpp"

#include <string_view>

struct Transform
{
public:
	void SetPosition(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
public:
	float x, y;

	double z_rotation;
};

class Sprite
{
public:
	Sprite(std::string_view path)
	{
		m_Tex = load(path.data());
	}

	~Sprite()
	{
		SDL_DestroyTexture(m_Tex);
		m_Tex = nullptr;
	}

	void Render()
	{
		SDL_Rect renderQuad = { transform.x, transform.y, m_Width, m_Height };
		SDL_RenderCopyEx(IronGL::m_Renderer, m_Tex, NULL, &renderQuad, transform.z_rotation, NULL, SDL_FLIP_NONE);
	}

	void ScreenCenter()
	{
		transform.SetPosition(WINDOW_WIDTH / 2 - (m_Width / 2), WINDOW_HEIGHT / 2 - (m_Height / 2));
	}

	void SetGraphicSize(double x)
	{
		m_Width *= x;
		m_Height *= x;
		transform.x -= m_Width / 4;
		transform.y -= m_Height / 4;
	}
public:
	Transform transform;
	int m_Width, m_Height;
private:
	SDL_Texture* m_Tex;
private:
	SDL_Texture* load(const char* path)
	{
		SDL_Texture* newTexture = nullptr;

		SDL_Surface* loadedSurface = IMG_Load(path);
		if (!loadedSurface)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
			exit(-1);
		}
		
		newTexture = SDL_CreateTextureFromSurface(IronGL::m_Renderer, loadedSurface);

		m_Width = loadedSurface->w;
		m_Height = loadedSurface->h;

		if (!newTexture)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
			exit(-1);
		}

		SDL_FreeSurface(loadedSurface);

		return newTexture;
	}
};