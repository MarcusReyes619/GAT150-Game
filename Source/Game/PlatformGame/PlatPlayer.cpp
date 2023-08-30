//#include "PlatPlayer.h"
//#include "Input/InputSystem.h"
//#include "Renderer/Renderer.h"
//#include "Framework/FrameWork.h"
//
//namespace kiko {
//
//	CLASS_DEFINITION(Player);
//
//	bool Player::Initialize()
//	{
//		Actor::Initialize();
//
//
//		m_physicsComp = GetComponent<kiko::PhyicsComponent>();
//		auto collisionComp = GetComponent<kiko::CollsionComponent>();
//		if (collisionComp) {
//
//			auto renderComp = GetComponent<kiko::RenderComponent>();
//			if (renderComp) {
//				float scale = transform.scale;
//				collisionComp->m_radius = GetComponent < kiko::RenderComponent>()->GetRadius() * scale;
//
//			}
//		}
//
//
//		return true;
//	}
//
//	void Player::Update(float dt)
//	{
//		Actor::Update(dt);
//
//		// movement
//		float dir = 0;
//		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
//		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
//		
//		
//		kiko::vec2 forward = kiko::vec2{ 1, 0 };
//
//		m_physicsComp->ApplyForce(forward * m_speed * dir);
//
//		//Jump
//		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE));
//		
//
//	}
//
//	void Player::OnCollisionEnter(Actor* other)
//	{
//		if (other->tag == "Enemy")
//		{
//
//			destroyed = true;
//			kiko::EventManger::Instance().DispatchEvent("OnPlayerDead", 0);
//
//			
//		}
//	}
//
//	void Player::Read(const json_t& value) {
//
//		Actor::Read(value);
//
//		READ_DATA(value, m_speed);
//		READ_DATA(value, jump);
//	}
//
//}