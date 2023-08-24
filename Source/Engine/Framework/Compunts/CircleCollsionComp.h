#pragma once
#include "CollsionComponent.h"
//#include "Framework/Factory.h"


namespace kiko {


	class CircleCollsionComponent : public CollsionComponent {
	public:
		CLASS_DECLARTION(CircleCollsionComponent)

		virtual void Update(float dt)override;
		virtual bool CheckCollision(CollsionComponent* collision)override;
	};

}
