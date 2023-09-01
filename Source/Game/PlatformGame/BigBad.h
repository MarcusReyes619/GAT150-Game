#pragma once
#pragma once

#include "Framework/Actor.h"

namespace kiko {
	class BigBad : public Actor {
	public:

		CLASS_DECLARTION(BigBad)


		bool Initialize()override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;


		
	};
}
