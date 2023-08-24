#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"


namespace kiko {


	class Weapon : public Actor
	{
	public:

		CLASS_DECLARTION(Weapon)

		bool Initialize()override;
		void Update(float dt)override;

		//void Read(const json_t& value);

		/*

		Weapon(float speed, const kiko::Transform& transform) :
			Actor{ transform},
			m_speed{ speed }
		{
			m_lifespan = 2.0f;
		}
		*/
		void OnCollision(Actor* other) override;

	private:
		float speed = 0;

	};
}
