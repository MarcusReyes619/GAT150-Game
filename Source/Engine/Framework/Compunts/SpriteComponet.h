#pragma once
#include "RenderCompunts.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"
#include "Renderer/Renderer.h"

namespace kiko {

	class SpriteComponent : public RenderComponent {

	public:
		
		CLASS_DECLARTION(SpriteComponent);

		bool Initialize()override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5f; }			

	public:
		Rect source;
		bool flipH = false;
		vec2 origin{ 0.5f, 0.5f };
		std::string textureName;
		res_t<Texture> m_texture;

	};

}
