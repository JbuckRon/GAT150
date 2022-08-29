#include "Engine.h"
#include "MyGame.h"
#include <iostream>

int main()
{
		
	neu::InitializeMemory();

	//file path
	neu::SetFilePath("../Assets");

	rapidjson::Document document;
	bool success = neu::Json::Load("json.txt", document);
	assert(success);
	std::string str;
	neu::Json::Get(document, "string", str);
	std::cout << str << std::endl;
	bool b;
	neu::Json::Get(document, "boolean", b);
	std::cout << b << std::endl;
	int i1;
	neu::Json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;
	int i2;
	neu::Json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;
	float f;
	neu::Json::Get(document, "float", f);
	std::cout << f << std::endl;
	neu::Vector2 v2;
	neu::Json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;
	neu::Color color;
	neu::Json::Get(document, "color", color);
	std::cout << color << std::endl;

	//initialize engine
	neu::g_renderer.Initialize();
	neu::g_inputSystem.Initialize();
	neu::g_audioSystem.Initialize();
	neu::g_resources.Initialize();
	//---init physics
	neu::g_eventManager.Initialize();

	neu::g_renderer.CreateWindow("Neumont", 800, 600);


	//load assets
	std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
	texture->Create(neu::g_renderer, "../Assets/Sprites/spaceShips_004.png");

	/*std::shared_ptr<neu::Model> model = std::make_shared<neu::Model>();
	model->Create("../Assets/Model/player.txt");*/


	neu::g_audioSystem.AddAudio("Laser", "../Assets/Audio/Laser_Shoot.wav");
	//create actors
	neu::Scene scene;


	std::unique_ptr<MyGame> game = std::make_unique<MyGame>();
	game->Initialize();

	auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
	actor->m_transform.position = { 600, 100 };
	actor->Initialize();

	scene.Add(std::move(actor));

	float angle = 0;
	bool quit = false;

	while (!quit)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		//update scene
		angle += 180.0f * neu::g_time.deltaTime;
		scene.Update();
		//render
		neu::g_renderer.BeginFrame();

		scene.Draw(neu::g_renderer);

		//neu::g_renderer.Draw(texture, { 400, 300 }, angle, {2, 2}, {0.5f, 1.0f});

		neu::g_renderer.EndFrame();
	}
	neu::Factory::Instance().Shutdown();
	neu::g_audioSystem.Shutdown();
	neu::g_inputSystem.Shutdown();
	neu::g_renderer.Shutdown();
	neu::g_eventManager.Shutdown();
}
