#pragma once

//#include "Mascot.cpp"
//#include "ObstacleHandler.cpp"
#include "Icon.cpp"

class MainGame : public Game
{
public:
	//First frame after initializing SDL 2
	MainGame()
		:clip("res/music/FutureWave.mp3"), icon(camera)
	{
		clip.m_Config.fast = true;
		clip.m_Config.loop = true;
		clip.Play();
	}

	//When the program is shuting down
	~MainGame()
	{
		//clip.~AudioClip();
		icon.~Icon();
	}

	//Every Frame ( Manage Logic )
	void Update()
	{
		clip.step();
		icon.Update(time);
	}

	//Every Frame ( Draw Images )
	void Render()
	{
		icon.Render();
	}

	void RenderUI()
	{
		ImGui::Begin("Camera Controller");
		ImGui::SliderFloat2("Camera Position", &camera.position.x, -200, 200);
		ImGui::SliderFloat("Camera FOV", &camera.m_Config.fov, 40, 200);
		ImGui::End();

		ImGui::Begin("Window Variables");
		ImGui::InputInt2("Size", &IronGL::m_WindowConfiguration.width);
		ImGui::InputText("Title", IronGL::m_WindowConfiguration.title.data(), IronGL::m_WindowConfiguration.title.capacity());
		ImGui::InputInt("Frames Cap", &IronGL::m_WindowConfiguration.fpsCap, 1, 100, 0);
		ImGui::Checkbox("Vsync", &IronGL::m_WindowConfiguration.vsync);

		if (ImGui::Button("Re-Build"))
		{
			IronGL::m_WindowConfiguration.writeToINI("./winConfig.ini");
			IronGL::m_WindowConfiguration.UpdateWinTitle(IronGL::m_Window);
			IronGL::m_WindowConfiguration.UpdateVsync(IronGL::m_Renderer);
			IronGL::m_WindowConfiguration.UpdateWinWH(IronGL::m_Window);
		}
		ImGui::End();
	}
public:
	Camera camera;
	Icon icon;
	AudioClip clip;
};