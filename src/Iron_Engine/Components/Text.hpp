#pragma once

#include <SDL_ttf.h>
#include <Iron_Engine/Engine.hpp>

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

class Text
{
public:
	Text(std::string_view path)
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
		data.clip.w = data.clip.w == 0 ? data.bounds.x : data.clip.w;
		data.clip.h = data.clip.h == 0 ? data.bounds.y : data.clip.h;

		clip = data.clip.w != 0 || data.clip.h != 0 ? &data.clip : NULL;

		SDL_Rect renderQuad =
		{ transform.position.x, transform.position.y,
			data.clip.w, data.clip.h };

		renderQuad.w *= transform.scale.x;
		renderQuad.h *= transform.scale.y;

		SDL_RenderCopyEx(IronGL::m_Renderer, m_Tex, clip, &renderQuad, transform.rotation, NULL, data.flip);
	}

	inline void ScreenCenter()
	{
		transform.position = { (float)WINDOW_WIDTH / 2 - (data.bounds.x * transform.scale.x / 2), (float)WINDOW_HEIGHT / 2 - (data.bounds.y * transform.scale.y / 2) };
	}
public:
	Transform transform;
	SpriteData data;
private:
	SDL_Texture* m_Tex;
	SDL_Rect* clip = NULL;
private:
	SDL_Texture* load(const char* path, SDL_Color textColor = {0xff, 0xff, 0xff})
	{
		//Get rid of preexisting texture
		free(m_Tex);

		SDL_Texture* text;

		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font,  path,  textColor);
		if (textSurface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
			exit(-1);
		}
		//Create texture from surface pixels
		text= SDL_CreateTextureFromSurface(IronGL::m_Renderer, textSurface);
		if (text== NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			exit(-1);
		}
		//Get image dimensions
		data.bounds.x = textSurface->w;
		data.bounds.y = textSurface->h;
		
		//Get rid of old surface
		SDL_FreeSurface(textSurface);

		//Return success
		return text;
	}

public:
	Sprite spr;
	TTF_Font* m_Font = NULL;
};