#include "CircleCollsionComp.h"
#include "Framework/Actor.h"

namespace kiko {

	CLASS_DEFINITION(CircleCollsionComponent)


	void CircleCollsionComponent::Update(float dt) {

	}

	bool CircleCollsionComponent::CheckCollision(CollsionComponent* collision)
	{
		float distance = m_owner->transform.position.Distance(collision->m_owner->transform.position);
		float radius = m_radius + collision->m_radius;

		return (distance <= radius);
	}

	void CircleCollsionComponent::Read(const json_t& value) {

	}
}

