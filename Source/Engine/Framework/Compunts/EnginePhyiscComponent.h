#pragma once
#include "PhysicComponent.h"

namespace kiko {
	class EnginePhysicComponet : public PhyicsComponent {
	public:
		CLASS_DECLARTION(EnginePhysicComponet);

		virtual void Update(float dt) override;
		virtual void ApplyForces(const vec2& force)override;
	};
}