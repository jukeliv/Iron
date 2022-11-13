#pragma once

#include "Iron_Engine\Core.hpp"

#include "Iron_Engine\Math\Vec2.hpp"

#include <string_view>

struct Transform
{
public:
	Vec2 position = { 0,0 };
	float z_rotation;
};

struct SpriteData
{
public:
	SDL_RendererFlip flip;
	Vec2 clip = { 0, 0 };
};

class Sprite
{
public:
	Sprite(std::string_view path)
		:m_Tex(load(path.data()))
	{
	}

	~Sprite()
	{
		SDL_DestroyTexture(m_Tex);
		m_Tex = nullptr;
	}

	void Render()
	{
		SDL_Rect renderQuad = { transform.position.x, transform.position.y, spr_data.clip.x, spr_data.clip.y };

		SDL_Point center; center.x = (float)spr_data.clip.x / 2; center.y = (float)spr_data.clip.y / 2;

		SDL_RenderCopyEx(IronGL::m_Renderer, m_Tex, NULL, &renderQuad, transform.z_rotation, &center, spr_data.flip);
	}

	void ScreenCenter()
	{
		transform.position = { (float)WINDOW_WIDTH / 2 - (spr_data.clip.x / 2), (float)WINDOW_HEIGHT / 2 - (spr_data.clip.y / 2) };
	}

	void SetGraphicSize(const double& x)
	{
		spr_data.clip *= x;
	}

	void SetGraphicSize(const Vec2& v)
	{
		spr_data.clip = v;
	}

	void SetGraphicSize(const int& w, const int& h)
	{
		spr_data.clip.y = h;
		spr_data.clip.x = w;
	}
public:
	Transform transform;
	SpriteData spr_data;
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
		spr_data.clip.x = loadedSurface->w;
		spr_data.clip.y = loadedSurface->h;

		if (!newTexture)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
			exit(-1);
		}

		SDL_FreeSurface(loadedSurface);

		return newTexture;
	}
};