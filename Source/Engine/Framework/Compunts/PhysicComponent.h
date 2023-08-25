#pragma once
#include "Component.h"
#include "Core/Vector2.h"

namespace kiko {
	class PhyicsComponent : public Component {
	public:
		virtual void Update(float dt) override = 0;
		virtual void ApplyForces(const vec2& force) = 0;

		virtual void SetVelocity(const vec2& velocity) { this->m_vel = velocity; }

	public :
		vec2 m_vel;
		vec2 m_acc;
		float m_mass = 1.0f;
		float m_damping = 0;
	};
}
