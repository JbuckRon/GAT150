#pragma once
#include "Framework/Game.h"

class MyGame : public neu::Game
{
public:
	enum gameState
	{
		titleScreen,
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

	void OnAddPoints(const neu::Event& event);
	void OnPlayerDead(const neu::Event& event);
private:
	gameState m_gameState = gameState::titleScreen;
	float m_stateTime = 3;
};