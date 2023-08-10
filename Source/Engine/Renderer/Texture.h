
#pragma once
#include "../Core/Vector2.h"
#include "Framework/Resources.h"
struct SDL_Texture;
namespace kiko
{
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();


		virtual bool Create(std::string filename, ...)override;
		bool Load(const std::string& filename, class Renderer& renderer);
		vec2 GetSize();

		//<make Renderer a friend class>

		friend class Renderer;
	private:
		SDL_Texture* m_texture = nullptr;
	};
}