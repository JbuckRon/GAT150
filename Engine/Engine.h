#pragma once
#include "Serialization/Json.h"

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"
#include "Core/Logger.h"

#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"
#include "Renderer/Font.h"
#include "Renderer/Model.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/ModelComponent.h"
#include "Components/TilemapComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/RBPhysicsComponent.h"
#include "Components/SpriteAnimComponent.h"
#include "Components/TextComponent.h"
#include "Components/CharacterComponent.h"
#include "Components/CameraComponent.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"
#include "Framework/EventManager.h"


#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Resource/ResourceManager.h"

#include "Physics/PhysicsSystem.h"

#include <memory>
#include <vector>
#include <list>
#include <variant>

namespace neu
{
	extern PhysicsSystem g_physicsSystem;
	extern AudioSystem g_audioSystem;
	extern Renderer g_renderer;
	extern InputSystem g_inputSystem;
	extern Time g_time;
	extern ResourceManager g_resources;
	extern EventManager g_eventManager;

	class Engine : public Singleton<Engine>
	{
	public:
		void Register();
	};
}