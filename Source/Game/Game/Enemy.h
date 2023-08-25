#pragma once
#include "Framework/Actor.h"


namespace kiko {


	class Enemy : public kiko::Actor
	{
	public:
		
	

		bool Initialize()override;
		void OnDestroy() override;

		void Update(float dt) override;
		void OnCollision(Actor* other) override;



	private:
		float m_speed = 0;
		float m_turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;


	

	};
}