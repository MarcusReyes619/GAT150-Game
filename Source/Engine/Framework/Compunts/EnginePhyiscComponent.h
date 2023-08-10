#include "PhysicComponent.h"

namespace kiko {
	class EnginePhysicComponet : public PhyicsComponent {
	public:
		void Update(float dt)override;
		void ApplyForces(const vec2& force)override;
	
	};
}