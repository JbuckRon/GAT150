#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>
namespace neu 
{
	void PlayerComponent::Initialize()
	{
		auto component = m_owner->GetComponent<CollisionComponent>();

		if (component)
		{
			component->SetCollisionEnter(std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1));
			component->SetCollisionExit(std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1));
		}
	}
	void PlayerComponent::Update()
	{
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
		
		auto component = m_owner->GetComponent<PhysicsComponent>();

		if (component)
		{
			component->ApplyForce(direction * speed);

		}

		if (g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * 500);
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
	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		if (other->GetName() == "Coin")
		{
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
		std::cout << "player exit\n";
	}
	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);
		return true;
	}
}
