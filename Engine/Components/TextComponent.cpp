#include "TextComponent.h"
#include "SDL_Surface.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Engine.h"

namespace neu
{
	void TextComponent::Update()
	{

	}

	void TextComponent::Draw(Renderer& renderer)
	{
		g_renderer.Draw(m_texture, m_owner->m_transform, registration);
	}

	void TextComponent::SetText(const std::string& text)
	{
		SDL_Surface* surface = m_font->CreateSurface(text, color);
		m_texture->CreateFromSurface(surface, g_renderer);
	}

	bool TextComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool TextComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, text);
		READ_DATA(value, font_name);
		READ_DATA(value, font_size);
		READ_DATA(value, registration);
		READ_DATA(value, color);

		m_font = g_resources.Get<Font>(font_name, font_size);
		m_texture = std::make_unique<Texture>();

		SetText(text);

		return true;
	}

}