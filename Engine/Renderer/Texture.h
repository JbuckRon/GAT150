#pragma once
#include "Math/Vector2.h"
#include "Resource/Resource.h"
#include <string>
struct SDL_Texture;

namespace neu {
	
	class Renderer;
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(const std::string& filename, ...);
		bool Create(Renderer& renderer, const std::string& filename);

		Vector2 GetSize() const;

		// !! allow Renderer to access private texture data (friend)
		friend class Renderer;
	private:
		SDL_Texture* m_texture = nullptr;
	};
}