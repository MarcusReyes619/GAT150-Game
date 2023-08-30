#pragma once
#include "Core/Core.h"
#include "Object.h"
#include "Renderer/Model.h"
#include "Framework/Compunts/Component.h"
#include <memory>


namespace kiko
{
	class Actor : public Object
	{


	public:
		CLASS_DECLARTION(Actor)

		Actor() = default;
		Actor(const kiko::Transform& transform) :
			transform{ transform }
		{}
		Actor(const kiko::Transform& transform, std::shared_ptr<Model> model) :
			transform{ transform },
			m_model{ model }
		{}
		Actor(const Actor& other);

		virtual ~Actor() {
			OnDestroy();
		}

		virtual bool Initialize()override;
		virtual void OnDestroy()override;

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> comp);
		template<typename T>
		T* GetComponent();

		//float GetRadius() { return (m_model) ? m_model->GetRadius() * transform.scale : -10000; }
		virtual void OnCollisionEnter(Actor* other) {}
		virtual void OnCollisionExit(Actor* other) {}

		void AddForce(const vec2& force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;



		//varabiles
		Transform transform;
		std::string tag;
		float lifespan = -1.0f;

		bool destroyed = false;
		bool persistent = false;
		bool prototype = false;


	protected:
		std::vector<std::unique_ptr<Component>> components;

		std::shared_ptr<Model> m_model;

		vec2 m_velocity;
		float m_damping = 0;
	};


	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& comp : components) {
			T* result = dynamic_cast<T*>(comp.get());
			if (result) return result;
		}
		return nullptr;
	}


}