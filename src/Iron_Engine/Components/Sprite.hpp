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
	SDL_Rect clip = {NULL};
}SpriteData;

class Sprite
{
public:
	Sprite(Transform& _transform, std::string_view path)
		: m_Tex(load(path.data())), transform(_transform)
	{
	}

	~Sprite()
	{
		SDL_DestroyTexture(m_Tex);
		m_Tex = nullptr;
	}

	void Render()
	{
		clip = data.clip.w != 0 || data.clip.h != 0 ? &data.clip : NULL;

		data.clip.w = data.clip.w == 0? data.bounds.x : data.clip.w;
		data.clip.h = data.clip.h == 0 ? data.bounds.y : data.clip.h;

		SDL_Rect renderQuad =
		{   transform.position.x, transform.position.y, 
			data.clip.w, data.clip.h };
		
		renderQuad.w *= transform.scale.x;
		renderQuad.h *= transform.scale.y;

		culling = (renderQuad.x - renderQuad.w > WINDOW_WIDTH || renderQuad.x + renderQuad.w < 0) || (renderQuad.y - renderQuad.h > WINDOW_HEIGHT || renderQuad.y + renderQuad.h < 0);

		if (culling)
			TRACE("CULLING SPR");
		else
			SDL_RenderCopyEx(IronGL::m_Renderer, m_Tex, clip, &renderQuad, transform.rotation, NULL, data.flip);
	}

	inline void ScreenCenter()
	{
		transform.position = { (float)WINDOW_WIDTH / 2 - (data.bounds.x * transform.scale.x / 2), (float)WINDOW_HEIGHT / 2 - (data.bounds.y * transform.scale.y / 2) };
	}
public:
	Transform& transform;
	SpriteData data;
	bool culling;
private:
	SDL_Texture* m_Tex;
	SDL_Rect* clip = NULL;
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