#pragma once
#include "Framework/Actor.h"
#include "Framework/Compunts/PhysicComponent.h"

namespace kiko {

	class BadBaral : public kiko::Actor {
	public:
		CLASS_DECLARTION(BadBaral)


			bool Initialize()override;
		void OnDestroy() override;

		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;


	};
}
