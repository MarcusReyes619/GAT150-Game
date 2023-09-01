#pragma once

#include "Framework/Actor.h"

namespace kiko {
	class Hammer : public Actor {
	public:

			CLASS_DECLARTION(Hammer)


				bool Initialize()override;

				void Update(float dt) override;
				void OnCollisionEnter(Actor* other) override;
				void OnCollisionExit(Actor* other) override;


		class PhyicsComponent* m_physicsComp = nullptr;
		//class SpriteComponent* m_spriteAnimationComp = nullptr;
	};
}