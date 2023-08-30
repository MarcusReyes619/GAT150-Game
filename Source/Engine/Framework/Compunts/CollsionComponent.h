#pragma once
#include "Component.h"

namespace kiko{
	class CollsionComponent : public Component {
	public:


		virtual bool CheckCollision(CollsionComponent* collision) { return true; }

	public:
			float m_radius = 0;
	};
}