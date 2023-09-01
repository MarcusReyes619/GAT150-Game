#pragma once
#include "Framework/Actor.h"


namespace kiko {
	class Player : public Actor

	{
	public:
		CLASS_DECLARTION(Player);


		bool Initialize()override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float m_speed = 0;
		float maxSpeed = 0;
		float jump = 0;
		int groundCount = 0;
		float timer = 10;
		float timeSpent = -1;

		
		class PhyicsComponent* m_physicsComp = nullptr;
		class AnimationComponet* m_spriteAnimationComp = nullptr;

	};
}
