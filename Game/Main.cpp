#include "Engine.h"
#include "MyGame.h"
#include <iostream>

int main()
{
	int r = math::Wrap(640, 0, 600);
		
	neu::InitializeMemory();
	//file path
	neu::SetFilePath("../Assets");

	//initialize engine
	neu::g_renderer.Initialize();
	neu::g_inputSystem.Initialize();
	neu::g_audioSystem.Initialize();
	neu::g_resources.Initialize();
	neu::g_physicsSystem.Initialize();
	neu::g_eventManager.Initialize();

	neu::Engine::Instance().Register();

	neu::g_renderer.CreateWindow("Neumont", 800, 600);
	neu::g_renderer.SetClearColor(neu::Color{ 0, 0, 0, 255 });

	std::unique_ptr<MyGame> game = std::make_unique<MyGame>();
	game->Initialize();

	bool quit = false;

	while (!quit)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();
		neu::g_physicsSystem.Update();
		neu::g_eventManager.Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		//update scene
		game->Update();

		//render
		neu::g_renderer.BeginFrame();
		game->Draw(neu::g_renderer);
		neu::g_renderer.EndFrame();
	}
	game->Shutdown();
	game.reset();

	neu::Factory::Instance().Shutdown();

	neu::g_physicsSystem.Shutdown();
	neu::g_audioSystem.Shutdown();
	neu::g_inputSystem.Shutdown();
	neu::g_renderer.Shutdown();
	neu::g_eventManager.Shutdown();
	neu::g_resources.Shutdown();
}
