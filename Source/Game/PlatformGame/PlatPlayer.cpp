#include "PlatPlayer.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/FrameWork.h"
//#include "Framework/Compunts/PhysicComponent.h"


namespace kiko {

	Player::Register regizter;;

	bool Player::Initialize()
	{
		Actor::Initialize();   


		m_physicsComp = GetComponent<kiko::PhyicsComponent>();
		m_spriteAnimationComp = GetComponent<AnimationComponet>();
		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		if (timeSpent != -1.0f) {
			timeSpent -= dt;
			
			if (timeSpent <= 0) {
				this->tag = "Player";
			}

		}
		
		// movement
		float dir = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		
		
		kiko::vec2 forward = kiko::vec2{ 1, 0 };

		m_physicsComp->ApplyForce(forward * m_speed * dir);

		//Jump

		bool onGround = (groundCount > 0);
	
		if (onGround &&
			kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

			kiko::vec2 up = kiko::vec2{ 0,-1 };
			m_physicsComp->SetVelocity(up * jump);
			
		}
		//animation
		vec2 vel = m_physicsComp->m_vel;
		//check if movin movin u
		
m_spriteAnimationComp->flipH = (dir < 0);

		if (tag != "HammerTime") {

			if (std::fabs(vel.x) > 0.2f) {
				
				m_spriteAnimationComp->SetSequence("Run");
			}

			else {
				m_spriteAnimationComp->SetSequence("idle");
			}

		}
		
		//Hammer Time
		

	}

	void Player::OnCollisionEnter(Actor* other)
	{
		//Barral
		if (other->tag == "Enemy")
		{

			destroyed = true;
			kiko::EventManger::Instance().DispatchEvent("OnPlayerDead", 0);
			

			
		}
		if (other->tag == "Ground") {
			groundCount++;
			//std::cout << "ree";
		}
		if (other->tag == "Ground2") {
			groundCount++;
			//std::cout << "ree";
		}

		//Collid with Hammer

		if (other->tag == "Hammer") {
			timeSpent = timer;

			this->tag = "HammerTime";

			m_spriteAnimationComp->SetSequence("HammerMan");
			std::cout << "ree";
		}


		

	}

	void Player::OnCollisionExit(Actor* other) {
		if (other->tag == "Ground")groundCount--;
		if (other->tag == "Ground2")groundCount--;
	}

	void Player::Read(const json_t& value) {

		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, jump);
		READ_DATA(value,maxSpeed);
	}

}