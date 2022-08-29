#pragma once
#include "Math/Rect.h"
#include "RenderComponent.h"

//CLASS_DECLARATION(SpriteComponent);
namespace neu
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{
	public:

		//std::unique_ptr<GameObject> Clone() override { CLASS_DECLARATION(SpriteComponent) };
		CLASS_DECLARATION(SpriteComponent)
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<Texture> m_texture;
	};
}