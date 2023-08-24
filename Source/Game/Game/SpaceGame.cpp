#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/FrameWork.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Initialize()
{
	

	kiko::ResourceManger rm;
	// create font / text objects
	m_font = GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font,"arcadeclassic.ttf",24));
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24));
	m_titleText->Create(kiko::g_renderer, "AZTEROIDS", kiko::Color{ 1, 1, 1, 1 });

	m_gameoverText = std::make_unique<kiko::Text>(m_font);
	m_gameoverText->Create(kiko::g_renderer, "GAME OVER", kiko::Color{ 1, 1, 1, 1 });

	m_timerText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24));
	m_timerText->Create(kiko::g_renderer, "TIMER", kiko::Color{ 1, 1, 1, 1 });

	// load audio
	kiko::g_audioSystem.AddAudio("hit", "hit.wav");

	// create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scene.json");
	m_scene->Initialize();

	//add Event
	kiko::EventManger::Instance().Subscribe("AddPoints", this, std::bind(&SpaceGame::AddPoints, this, std::placeholders::_1));
	kiko::EventManger::Instance().Subscribe("OnPlayerDead", this, std::bind(&SpaceGame::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName("Background");
		}
		break;

	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		//create player
		std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 3 });
		player->tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9f);
		//m_scene->Add(std::move(player));
		//create components
		//std::unique_ptr<kiko::ModelRenderComponent> comp = std::make_unique<kiko::SpriteComponent>();

		//adding compoents

		//kiko::Factory::Instance().Create<kiko::SpriteComponent>("SpriteComponent");//std::make_unique<kiko::SpriteComponent>();

		auto renderComp = CREATE_CLASS(SpriteComponent);

		renderComp->m_texture = GET_RESOURCE(kiko::Texture, "Ship_2_C_Small.png", kiko::g_renderer);
		player->AddComponent(std::move(renderComp));

		auto physicComp = CREATE_CLASS(EnginePhysicComponet); //std::make_unique<kiko::EnginePhysicComponet>();
		physicComp->m_damping = 0.9f;
		player->AddComponent(std::move(physicComp));
		
		auto collisonComp = std::make_unique<kiko::CircleCollsionComponent>();
		collisonComp->m_radius = 30.0f;
		player->AddComponent(std::move(collisonComp));

		player->Initialize();

		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
	break;
	case SpaceGame::eState::Game:
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			//std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 3 });

			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(20.0f,kiko::Pi,kiko::Transform{{400,300},0,3});
			enemy->tag = "Enemy";
			enemy->m_game = this;

			auto renderComp = std::make_unique<kiko::SpriteComponent>();

			renderComp->m_texture = GET_RESOURCE(kiko::Texture, "Ship_2_C_Small.png");
			enemy->AddComponent(std::move(renderComp));

			auto collisonComp = std::make_unique<kiko::CircleCollsionComponent>();
			collisonComp->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisonComp));

			

			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		break;

	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;

	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), {1, 1, 1, 1});
	m_timerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer & renderer)
{
	m_scene->Draw(renderer);

	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 400, 300);
	}

	m_timerText->Draw(renderer, 400, 40);
	m_scoreText->Draw(renderer, 40, 20);
	
}

void SpaceGame::AddPoints(const kiko::Event& event){
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const kiko::Event event)
{
	m_state = eState::PlayerDeadStart;
}
