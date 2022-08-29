#pragma once
#include "GameObject.h"
namespace neu
{
	class Actor;

	class Component : public GameObject, public Iserializable
	{
	public:
		Component() = default;

		virtual void Initialize() override {}
		virtual void Update() = 0;

		friend class Actor;

	protected:
		Actor* m_owner = nullptr;
	};
}