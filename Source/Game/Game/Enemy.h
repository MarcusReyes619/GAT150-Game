#pragma once
#include "Framework/Actor.h"
#include "Framework/Compunts/PhysicComponent.h"



namespace kiko {

	class Enemy : public kiko::Actor
	{
	public:
		CLASS_DECLARTION(Enemy)


			bool Initialize()override;
		void OnDestroy() override;

		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;



	public:
		float m_speed = 0;
		float m_turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;

		kiko::PhyicsComponent* m_physicsComp = nullptr;



	};
}