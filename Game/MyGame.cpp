#include "MyGame.h"
#include "Engine.h"
#include "GameComponents/EnemyComponent.h"

void MyGame::Initialize()
{
	REGISTER_CLASS(EnemyComponent)

		neu::g_audioSystem.AddAudio( "coin", "Audio/coin.wav");
		neu::g_audioSystem.AddAudio( "jump", "Audio/jump.wav");

	m_scene = std::make_unique<neu::Scene>();
	rapidjson::Document document;

	std::vector<std::string> sceneNames = { "scenes/prefabs.txt", "scenes/tilemap.txt", "scenes/level.txt" };


	for (auto sceneName : sceneNames) 
	{
		bool success = neu::Json::Load(sceneName, document);

		if (!success)
		{
			LOG("could not load scene %s", sceneName.c_str());
			continue;
		}
		m_scene->Read(document);
	}
	m_scene->Initialize();
	//placeholder

	

	neu::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&MyGame::OnNotify, this, std::placeholders::_1));
	neu::g_eventManager.Subscribe("EVENT_PLAYER_DEAD", std::bind(&MyGame::OnNotify, this, std::placeholders::_1));
}

void MyGame::Shutdown()
{
	m_scene->RemoveAll();
}

void MyGame::Update()
{
	if (m_gameTimer > 0)
	{
	m_gameTimer -= neu::g_time.deltaTime;

	}
	switch (m_gameState)
	{
	case MyGame::titleScreen:
		if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::KeyState::Pressed)
		{
			m_scene->GetActorFromName("Title")->SetActive(false);

			m_gameState = gameState::startLevel;
		}
		break;
	case MyGame::startLevel:
	{
		if (spawnPlayer)
		{
		auto actor = neu::Factory::Instance().Create<neu::Actor>("Player");
		actor->m_transform.position = { 400.0f, 100.0f };
		actor->Initialize();

		m_scene->Add(std::move(actor));
		}
	}

	if (m_gameTimer > 0)
	{
		for (int i = 0; i < 5; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
			actor->m_transform.position = { neu::randomf(200 ,600), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
	}
		m_gameState = gameState::game;
		break;
	case MyGame::game:
		spawnPlayer = false;
		if (coinCount == 5)
		{
			m_gameState = playerDead;
			coinCount = 0;
		}
		break;
	case MyGame::playerDead:
		m_stateTimer -= neu::g_time.deltaTime;
		if (m_stateTimer <= 0)
		{
			m_gameState = (m_lives > 0) ? gameState::startLevel : gameState::gameOver;
		}
		break;
	case MyGame::gameOver:
		m_gameState = gameState::titleScreen;
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

void MyGame::OnNotify(const neu::Event& event)
{


	if (event.name == "EVENT_ADD_POINTS")
	{
		AddPoints(std::get<int>(event.data));
		coinCount++;
	}
	
	if (event.name == "EVENT_PLAYER_DEAD")
	{
		m_gameState = gameState::playerDead;
		m_lives--;
		m_stateTimer = 3;
	}
}

void MyGame::OnAddPoints(const neu::Event& event)
{
	int points = std::get<int>(event.data);
	AddPoints(points);

	std::cout << event.name << std::endl;
	std::cout << std::get<int>(event.data) << std::endl;

}

void MyGame::OnPlayerDead(const neu::Event& event)
{
	m_gameState = gameState::playerDead;
	m_lives--;
	m_stateTimer = 3;
}
