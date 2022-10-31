#pragma once

#include "Iron_Engine\Core.hpp"

#include <string_view>

struct Transform
{
public:
	void SetPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
public:
	float x, y;

	double z_rotation;
};

struct SpriteData
{
public:
	SDL_RendererFlip flip;
	int w, h;
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
		SDL_Rect renderQuad = { transform.x, transform.y, spr_data.w, spr_data.h };

		SDL_RenderCopyEx(IronGL::m_Renderer, m_Tex, NULL, &renderQuad, transform.z_rotation, NULL, spr_data.flip);
	}

	void ScreenCenter()
	{
		transform.SetPosition(WINDOW_WIDTH / 2 - (spr_data.w / 2), WINDOW_HEIGHT / 2 - (spr_data.h / 2));
	}

	void SetGraphicSize(double x)
	{
		spr_data.h *= x;
		spr_data.w *= x;
		/*TODO: Figure out how to center this shit
		transform.x -= pow(x,4);
		transform.y -= pow(x,4);
		*/
	}
public:
	Transform transform;
	SpriteData spr_data;
private:
	SDL_Texture* m_Tex;
	int m_Width, m_Height;
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

		spr_data.w = m_Width;
		spr_data.h = m_Height;

		if (!newTexture)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
			exit(-1);
		}

		SDL_FreeSurface(loadedSurface);

		return newTexture;
	}
};