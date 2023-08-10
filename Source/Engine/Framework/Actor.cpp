#include "Actor.h"
#include "Compunts/RenderCompunts.h"

namespace kiko
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}
		for (auto& comp : m_components) {
			comp->Update(dt);
		}

	}

	void Actor::Draw(kiko::Renderer& renderer)
	{
	
		for (auto& comp : m_components) {
			RenderComponent* renderCompoent = dynamic_cast<RenderComponent*>(comp.get());
			if (dynamic_cast<RenderComponent*>(comp.get())) {

				renderCompoent->Draw(renderer);

			}
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> comp)
	{
		comp->m_owner = this;
		m_components.push_back(std::move(comp));
	}
}
