#pragma once

#include <Iron_Engine/Engine.hpp>
#include <string_view>

typedef struct AnimationData
{
	AnimationData(std::string_view _prefix, std::vector<SDL_Rect> _rects, bool _loops = true)
		:prefix(_prefix.data()), rects(_rects), loops(_loops){}
	std::string prefix;
	std::vector<SDL_Rect> rects;
	bool loops;
}AnimationData;

class Animator
{
public:
	Animator(std::string_view path)
		: spr(path), time(0)
	{
	}

	void AddByRects(std::string_view prefix, std::vector<SDL_Rect> rects, bool loops = true)
	{
		AnimationData data(prefix, rects, loops);
		animations.push_back(data);
	}

	void PlayAnim(std::string_view prefix)
	{
		anim = "";

		for (size_t i = 0; i < animations.size(); i++)
		{
			AnimationData a = animations.at(i);
			if (a.prefix == prefix) {
				std::cout<<"Succesfully loaded " << prefix.data() << std::endl;
				anim = prefix.data();
				anim_index = i;
				break;
			}
		}

		if (anim.empty())
		{
			std::cout << "Animation " << prefix.data() << " does not exist" << std::endl;
			exit(-1);
		}
		
		time = 0;
		cur_rect = 0;

		spr.data.clip = animations[anim_index].rects[cur_rect];
	}

	void step(const Time& _time)
	{
		if (anim.empty())
			return;

		time += _time.delta;

		if (time > anim_index + 1 && time < anim_index + 2)
		{
			cur_rect++;


			if (cur_rect > animations[anim_index].rects.size() - 1)
			{
				if (animations[anim_index].loops)
					cur_rect = 0;
				else
					cur_rect = Matloon::clamp(cur_rect, 0, animations[anim_index].rects.size() - 1);
			}

			time = 0;
		}

		spr.data.clip = animations[anim_index].rects[cur_rect];
	}
public:
	Sprite spr;
	float time = 0;
	std::string anim = "";
	int anim_index = 0;
	int cur_rect = 0;
private:
	std::vector<AnimationData> animations;
};