#pragma once

#include <Iron_Engine\Core.hpp>

#include "glm/glm.hpp"
#include <string_view>

typedef struct Transform
{
public:
	glm::vec2 position = { 0,0 };
	glm::vec2 scale = { 1,1 };
	float rotation;
}Transform;

typedef struct SpriteData
{
public:
	SDL_RendererFlip flip;
	glm::vec2 bounds = { 0, 0 };
	SDL_Rect* clip = NULL;//TODO: Implement this with the entire Sprite class
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
		SDL_Rect renderQuad = { transform.position.x, transform.position.y, data.bounds.x * transform.scale.x, data.bounds.y * transform.scale.y };
		SDL_RenderCopyEx(IronGL::m_Renderer, m_Tex, NULL, &renderQuad, transform.rotation, NULL, data.flip);
	}

	void ScreenCenter()
	{
		transform.position = { (float)WINDOW_WIDTH / 2 - (data.bounds.x / 2), (float)WINDOW_HEIGHT / 2 - (data.bounds.y / 2) };
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
		data.bounds.x = loadedSurface->w;
		data.bounds.y = loadedSurface->h;

		if (!newTexture)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
			exit(-1);
		}

		SDL_FreeSurface(loadedSurface);

		return newTexture;
	}
};