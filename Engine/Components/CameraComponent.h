#pragma once
#include "Framework/Component.h"
#include "Math/Matrix3x3.h"

namespace neu
{
	class CameraComponent : public Component
	{
	public :
		CLASS_DECLARATION(CameraComponent)

		virtual void Update() override;

		void SetViewport(const Vector2& position, const Vector2& size);
		
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Matrix3x3 m_view;
		Matrix3x3 m_viewport;
	};
}