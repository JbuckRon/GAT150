#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>
namespace neu 
{
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();

	}
	void PlayerComponent::Update()
	{
		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if (camera)
		{
			camera->m_transform.position = math::Lerp(camera -> m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
		}

		Vector2 direction = Vector2::zero;

		if (g_inputSystem.GetKeyState(key_left) == InputSystem::KeyState::Held)
		{
			//m_owner->m_transform.rotation -= 180 * g_time.deltaTime;
			direction = Vector2::left;
		}
		
		if (g_inputSystem.GetKeyState(key_right) == InputSystem::KeyState::Held)
		{
			//m_owner->m_transform.rotation += 180 * g_time.deltaTime;
			direction = Vector2::right;
		}
		
		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			// if in the air (m_groundCount == 0) then reduce force
			float multiplier = (m_groundCount > 0) ? 1 : 0.2f;
			component->ApplyForce(direction * speed * multiplier);
			velocity = component->m_velocity;
		}

		if (m_groundCount > 0 && g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			neu::g_audioSystem.PlayAudio("jump");

			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * 500);
			}
			auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
			if (animComponent)
			{
				if (velocity.x != 0) animComponent->SetFlipHorizontal(velocity.x < 0);
				if (std::fabs(velocity.x) > 0)
				{
					animComponent->SetSequence("run");
				}
				else
				{
					animComponent->SetSequence("idle");
				}
			}

		}
		//float thrust = 0;
		//if (g_inputSystem.GetKeyState(key_up) == InputSystem::KeyState::Held)
		//{
		//	thrust = 100;
		//}
		//
		//if (g_inputSystem.GetKeyState(key_down) == InputSystem::KeyState::Held)
		//{
		//	
		//}

		//auto component = m_owner->GetComponent<PhysicsComponent>();
		//if (component)
		//{
		//	//thrust
		//	Vector2 force = Vector2::Rotate({ 1, 0 }, math::DegToRad(m_owner->m_transform.rotation)) * thrust;
		//	component->ApplyForce(force);

		//	//gravity
		//	force = (Vector2{ 400, 300 } - m_owner->m_transform.position).Normalized() * 100.0f;
		//	component->ApplyForce(force);
		//}
		//m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

		//if (neu::g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		//{
		//	auto component = m_owner->GetComponent<AudioComponent>();
		//	if (component != nullptr)
		//	{
		//		component->Play();
		//	}
		//}
	}
	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.data);
			if (health <= 0)
			{
				m_owner->SetDestroy();

				Event event;
				event.name = "EVENT_PLAYER_DEAD";

				g_eventManager.Notify(event);
			}
		}
		
	}
	void PlayerComponent::OnCollisionEnter(Actor* other)
	{

		if (other->GetTag() == "Ground")
		{
			m_groundCount++;
		}

		if (other->GetName() == "Coin")
		{
			neu::g_audioSystem.PlayAudio("coin");

			Event event;
			event.name = "EVENT_ADD_POINTS";
			event.data = 100;

			g_eventManager.Notify(event);
			other->SetDestroy();
		}
		std::cout << "player enter\n";
	}
	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		if (other->GetTag() == "Ground")
		{
			m_groundCount--;
		}

		std::cout << "player exit\n";
	}
	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);

		READ_DATA(value, jump);
		READ_DATA(value, health);
		READ_DATA(value, damage);
		return true;
	}
}
