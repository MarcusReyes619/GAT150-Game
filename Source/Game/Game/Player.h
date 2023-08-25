#pragma once
#include "Framework/Actor.h"
#include "Framework/Compunts/PhysicComponent.h"

namespace kiko {
	class Player : public Actor

	{
	public:
		CLASS_DECLARTION(Player);

		
		/*Player(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			turnRate{ turnRate }
		{}*/

		bool Initialize()override;

		void Update(float dt) override;
		void OnCollision(Actor* other) override;

	private:
		float m_speed = 0;
		float turnRate = 0;

		kiko::PhyicsComponent* m_physicsComp = nullptr;
	};
}