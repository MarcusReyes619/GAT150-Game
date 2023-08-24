#include "Actor.h"
#include "Compunts/RenderCompunts.h"

namespace kiko
{
	CLASS_DEFINITION(Actor);
	
	

	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;

		for (auto& component : components) {
			auto cloneComponent = std::unique_ptr<Component>((Component*)component->Clone().release());
				AddComponent(std::move(cloneComponent));
		}
	}

	bool Actor::Initialize()
	{
		for (auto& comp : components) {
			comp->Initialize();
		}
		return true;
	}
	void Actor::OnDestroy()
	{
		for (auto& comp : components) {
			comp->OnDestroy();
		}
	}
	void Actor::Update(float dt)
	{
		if (lifespan != -1.0f)
		{
			lifespan -= dt;
			destroyed = (lifespan <= 0);
		}
		for (auto& comp : components) {
			comp->Update(dt);
		}

	}

	void Actor::Draw(kiko::Renderer& renderer)
	{
	
		for (auto& comp : components) {
			RenderComponent* renderCompoent = dynamic_cast<RenderComponent*>(comp.get());
			if (dynamic_cast<RenderComponent*>(comp.get())) {

				renderCompoent->Draw(renderer);

			}
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> comp)
	{
		comp->m_owner = this;
		components.push_back(std::move(comp));
	}

	void Actor::Read(const rapidjson::Value& value) {

		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);
		READ_DATA(value, active);

		if (HAS_DATA(value, transform)) transform.Read(value);

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type)
					component->Read(componentValue);
				AddComponent(std::move(component));
			}
		}

	}
}
