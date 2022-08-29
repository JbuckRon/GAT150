#include "MyGame.h"
#include "Engine.h"
#include "Framework/Event.h"
void MyGame::Initialize()
{
	m_scene = std::make_unique<neu::Scene>();
	//std::vector<std::string> sceneNames = { "scenes/prefabs.txt", "scenes/tilemap.txt", "scenes/level.txt" };

	/*for (auto sceneName : sceneNames) 
	{
		bool success = neu::Json::Load(sceneName, document);

		if (!success)
		{
			LOG("could not load scene %s", sceneName.c_str());
			continue;
		}
		m_scene->Read(document);
	}
	m_scene->Initialize();*/
	//placeholder

	neu::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&MyGame::OnAddPoints, this, std::placeholders::_1));
}

void MyGame::Shutdown()
{
	//m_scene->RemoveAll();
}

void MyGame::Update()
{
	switch (m_gameState)
	{
	case MyGame::titleScreen:
		break;
	case MyGame::game:
		break;
	case MyGame::gameOver:
		break;
	default:
		break;
	}
	m_scene->Update();
}

void MyGame::Draw(neu::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void MyGame::OnAddPoints(const neu::Event& event)
{
	AddPoints(std::get<int>(event.data));

	std::cout << event.name << std::endl;
	std::cout << std::get<int>(event.data) << std::endl;
}

void MyGame::OnPlayerDead(const neu::Event& event)
{
	m_gameState = gameState::gameOver;
}
