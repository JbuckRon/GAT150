#include "Engine.h"

namespace neu
{
	PhysicsSystem g_physicsSystem;
	AudioSystem g_audioSystem;
	Renderer g_renderer;
	InputSystem g_inputSystem;
	Time g_time;
	ResourceManager g_resources;
	EventManager g_eventManager;

	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(TilemapComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(RBPhysicsComponent);
		REGISTER_CLASS(SpriteAnimComponent);
		REGISTER_CLASS(TextComponent);
		
	}

}