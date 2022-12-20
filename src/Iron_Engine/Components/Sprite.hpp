#pragma once

#include <Iron_Engine\Core.hpp>
#include <Iron_Engine/Utils/Camera.hpp>

#include "glm/glm.hpp"
#include <string_view>

typedef struct Transform
{
public:
	glm::vec2 position = { 0,0 };
	glm::vec2 scale = { 1,1 };
	float rotation = 0.0f;
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

	void Render(Camera& camera)
	{
		clip = data.clip.w || data.clip.h ? &data.clip : NULL;

		data.clip.w = data.clip.w? data.clip.w : data.bounds.x;
		data.clip.h = data.clip.h? data.clip.h : data.bounds.y;
		
		glm::vec2 translate = camera.TranslatePosition(transform.position);

		SDL_Rect renderQuad =
		{   translate.x , translate.y,
		data.clip.w, data.clip.h };
		
		renderQuad.w *= (float)transform.scale.x * camera.getScale();
		renderQuad.h *= (float)transform.scale.y * camera.getScale();

		// Check if the texture is out of the screen
		culling = (renderQuad.x - renderQuad.w > IronGL::m_WindowConfiguration.width || renderQuad.x + renderQuad.w < 0) || (renderQuad.y - renderQuad.h > IronGL::m_WindowConfiguration.height || renderQuad.y + renderQuad.h < 0);

		// Draw texture onto the screen if it is not out of bounds
		if (!culling)
		{
			clip = data.clip.w != 0 || data.clip.h != 0 ? &data.clip : NULL;
			SDL_RenderCopyEx(IronGL::m_Renderer, m_Tex, clip, &renderQuad, transform.rotation, NULL, data.flip);
		}
	}

	inline void ScreenCenter()
	{
		transform.position = { (float)IronGL::m_WindowConfiguration.width / 2 - (data.bounds.x * transform.scale.x / 2), (float)IronGL::m_WindowConfiguration.height / 2 - (data.bounds.y * transform.scale.y / 2) };
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