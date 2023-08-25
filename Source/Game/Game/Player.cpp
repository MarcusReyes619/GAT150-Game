#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/FrameWork.h"

namespace kiko {

	CLASS_DEFINITION(Player);

	bool Player::Initialize()
	{
		Actor::Initialize();


		m_physicsComp = GetComponent<kiko::PhyicsComponent>();
		auto collisionComp = GetComponent<kiko::CollsionComponent>();
		if (collisionComp) {

			auto renderComp = GetComponent<kiko::RenderComponent>();
			if (renderComp) {
				float scale = transform.scale;
				collisionComp->m_radius = GetComponent < kiko::RenderComponent>()->GetRadius() * scale;

			}
		}


		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		float rotate = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		//transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();
		m_physicsComp->ApplyTorque(rotate * turnRate);

		float thrust = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);



		m_physicsComp->ApplyForce(forward * m_speed * thrust);

		//AddForce(forward * m_speed * thrust);


		//m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

		// fire weapon
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{

			auto weapon = kiko::Factory::Instance().Create<kiko::Weapon>("RocketPew");
			weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), transform.scale };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));

			//	// create weapon
			//	kiko::Transform transform1{ transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
			//	std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 400.0f, transform1);
			//	weapon->m_tag = "Player";
			//	std::unique_ptr<kiko::SpriteComponent> comp = std::make_unique<kiko::SpriteComponent>();
			//	comp->m_texture = GET_RESOURCE(kiko::Texture, "RocketPew.png", kiko::g_renderer);
			//	weapon->AddComponent(std::move(comp));

			//	auto collisonComp = std::make_unique<kiko::CircleCollsionComponent>();
			//	collisonComp->m_radius = 30.0f;
			//	weapon->AddComponent(std::move(collisonComp));

			//	weapon->Initialize();
			//	m_scene->Add(std::move(weapon));

			//	kiko::Transform transform2{ transform.position, transform.rotation - kiko::DegreesToRadians(10.0f), 1 };
			//	weapon = std::make_unique<Weapon>(400.0f, transform2);
			//	weapon->m_tag = "Player";

			//	comp = std::make_unique<kiko::SpriteComponent>();
			//	comp->m_texture = GET_RESOURCE(kiko::Texture, "RocketPew.png", kiko::g_renderer);;
			//	weapon->AddComponent(std::move(comp));
			//	collisonComp = std::make_unique<kiko::CircleCollsionComponent>();
			//	collisonComp->m_radius = 30.0f;
			//	weapon->AddComponent(std::move(collisonComp));

			//	weapon->Initialize();
			//	m_scene->Add(std::move(weapon));
		}

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
		else kiko::g_time.SetTimeScale(1.0f);

	}

	void Player::OnCollision(Actor* other)
	{
		if (other->tag == "Enemy")
		{

			destroyed = true;
			kiko::EventManger::Instance().DispatchEvent("OnPlayerDead", 0);

			/*m_game->SetLives(m_game->GetLives() - 1);
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);*/
		}
	}
	
	void Player::Read(const json_t& value) {

		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, turnRate);
	}

}