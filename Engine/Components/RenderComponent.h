#pragma once
#include "Framework/Component.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"
namespace neu
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;

		virtual Rect& GetSource() { return source; }

		void SetFlipHorizontal(bool flip = true) { flipHorizontal = flip; }
		bool GetFlipHorizontal() { return flipHorizontal; }

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	protected:
		float sort_order;
		Rect source;
		bool flipHorizontal = false;
		Vector2 registration = Vector2{ 0.5f, 0.5f };
	};
}