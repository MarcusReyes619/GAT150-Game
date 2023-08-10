#include "EnginePhyiscComponent.h"
#include "Framework/Actor.h"

namespace kiko{
void EnginePhysicComponet::Update(float dt)
{
	m_owner->m_transform.position += m_vel * dt;
	m_vel *= std::pow(1.0f - m_damping, dt);
}

void EnginePhysicComponet::ApplyForces(const vec2& force)
{
	m_vel += force;
}

}




