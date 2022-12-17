#include<Iron_Engine/Engine.hpp>

class Icon : public GameObject
{
public:
	Icon(Camera& camera)
		: camera(camera), spr(transform, "res/images/slime.png")
	{
		animator = std::make_unique<Animator>(spr);

		transform.scale = glm::vec2(4);
		spr.ScreenCenter();

		animator->AddByRects("idle", { {0, 0, 21, 21}, {0, 21, 21, 21}, {21, 0, 21, 21}, {0, 21, 21, 21} }, 3);

		animator->PlayAnim("idle");
	}

	void Update(const Time& time)
	{
		animator->step(time);
	}

	void Render()
	{
		spr.Render(camera);
	}

	~Icon()
	{
		spr.~Sprite();
		animator.release();
		delete animator.get();
	}
private:
	std::unique_ptr<Animator> animator;
	Sprite spr;
	Transform transform;
	Camera& camera;
};