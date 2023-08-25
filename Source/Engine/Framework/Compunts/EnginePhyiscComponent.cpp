#include "EnginePhyiscComponent.h"
#include "Framework/Actor.h"

namespace kiko{
	
	CLASS_DEFINITION(EnginePhysicComponet);

	void EnginePhysicComponet::Update(float dt)
	{
		m_owner->transform.position += m_vel * dt;
		m_vel *= std::pow(1.0f - m_damping, dt);
	}

	void EnginePhysicComponet::ApplyForce(const vec2& force)
	{
		m_vel += force;
	}
	void EnginePhysicComponet::ApplyTorque(float torque)
	{
	}
	void EnginePhysicComponet::Read(const json_t& value) {

	}

}




