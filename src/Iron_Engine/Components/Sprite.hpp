#pragma once

#include "Iron_Engine\Core.hpp"

#include "Iron_Engine\Math\Vec2.hpp"

#include <string_view>

typedef struct Transform
{
public:
	Vec2 position = { 0,0 };
	float z_rotation;
}Transform;

typedef struct SpriteData
{
public:
	SDL_RendererFlip flip;
	Vec2 clip = { 0, 0 };
}SpriteData;

class Sprite
{
public:
	Sprite(std::string_view path)
		: m_Tex(load(path.data()))
	{
	}

	~Sprite()
	{
		SDL_DestroyTexture(m_Tex);
		m_Tex = nullptr;
	}

	void Render()
	{
		SDL_Rect renderQuad = { transform.position.x, transform.position.y, data.clip.x, data.clip.y };

		SDL_RenderCopyEx(IronGL::m_Renderer, m_Tex, NULL, &renderQuad, transform.z_rotation, NULL, data.flip);
	}

	void ScreenCenter()
	{
		transform.position = { (float)WINDOW_WIDTH / 2 - (data.clip.x / 2), (float)WINDOW_HEIGHT / 2 - (data.clip.y / 2) };
	}

	void SetGraphicSize(const double& x)
	{
		data.clip *= x;
	}

	void SetGraphicSize(const Vec2& v)
	{
		data.clip = v;
	}

	void SetGraphicSize(const int& w, const int& h)
	{
		data.clip.y = h;
		data.clip.x = w;
	}
public:
	Transform transform;
	SpriteData data;
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
		data.clip.x = loadedSurface->w;
		data.clip.y = loadedSurface->h;

		if (!newTexture)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
			exit(-1);
		}

		SDL_FreeSurface(loadedSurface);

		return newTexture;
	}
};