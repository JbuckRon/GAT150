#include "Engine.h"
#include <iostream>


int main()
{
	std::cout << "Hello world" << std::endl;
	neu::InitializeMemory();

	//file path
	neu::SetFilePath("../Assets");

	//initialize engine
	neu::g_renderer.Initialize();
	neu::g_inputSystem.Initialize();
	neu::g_audioSystem.Initialize();

	neu::g_renderer.CreateWindow("XXX", 800, 600);

	
	bool quit = false;

	while (!quit)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		//render
		neu::g_renderer.BeginFrame();

		neu::g_renderer.EndFrame();
	}
	neu::g_audioSystem.Shutdown();
	neu::g_renderer.Shutdown();
}
