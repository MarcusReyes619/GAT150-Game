#pragma once
#include "Component.h"

namespace kiko{
	class CollsionComponent : public Component {
	public:
		virtual bool CheckCollision(CollsionComponent* collision);

	public:
			float m_radius = 0;
	};
}