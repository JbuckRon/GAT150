#pragma once
#include "CharacterComponent.h"
#include "Framework/Event.h"
#include "Framework/Component.h"
#include "Physics/Collision.h"
namespace neu
{
	class PlayerComponent : public CharacterComponent
	{
	public:
		PlayerComponent() = default;

		CLASS_DECLARATION(PlayerComponent)

		void Initialize() override;
		void Update() override;

		virtual void OnNotify(const Event& event) override;
		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		int m_groundCount = 0;

		float jump = 300.0f;

	};
}