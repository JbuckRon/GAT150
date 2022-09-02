#pragma once
#include "Engine.h"



class MyGame : public neu::Game, public neu::INotify
{
public:
	enum gameState
	{
		titleScreen,
		startLevel,
		game,
		playerDead,
		gameOver
	};
public:
	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(neu::Renderer& renderer) override;
	virtual void OnNotify(const neu::Event& event) override;


	void OnAddPoints(const neu::Event& event);
	void OnPlayerDead(const neu::Event& event);
private:
	gameState m_gameState = gameState::titleScreen;
	int m_lives = 3;
	float m_stateTimer = 3;
	float m_gameTimer = 60;
	int coinCount = 0;
	bool spawnPlayer = true;
};