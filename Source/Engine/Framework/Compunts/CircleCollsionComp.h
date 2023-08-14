#pragma once
#include "CollsionComponent.h"

namespace kiko {
	class CircleCollsionComponent : public CollsionComponent {

		virtual void Update(float dt)override;
		virtual bool CheckCollision(CollsionComponent* collision)override;
	};
}
