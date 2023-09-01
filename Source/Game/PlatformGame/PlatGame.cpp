#include "PlatGame.h"
#include "badBaral.h"
#include "Framework/FrameWork.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool PlatGame::Initialize()
{


	

	// load audio
	//kiko::g_audioSystem.AddAudio("hit", "hit.wav");

	// create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("Scenes/PlatScene.json");
	m_scene->Load("scenes/tilemap.json");
	m_scene->Initialize();

	//m_scene->GetActorByName("Title")->active = false;
	//add Event
	kiko::EventManger::Instance().Subscribe("AddPoints", this, std::bind(&PlatGame::AddPoints, this, std::placeholders::_1));
	kiko::EventManger::Instance().Subscribe("OnPlayerDead", this, std::bind(&PlatGame::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void PlatGame::Shutdown()
{
}

void PlatGame::Update(float dt)
{

	m_gameTimer += dt;
	m_spawnTimer += dt;
	if (m_spawnTimer >= m_spawnTime)
	{
		m_spawnTimer = 0;

		auto barl = INSTIANTIATE(BadBaral, "BadBaral");
		barl->transform = kiko::Transform{ {500,0 }, kiko::randomf(kiko::TwoPi), 1 };
		barl->Initialize();
		m_scene->Add(std::move(barl));
	}
	

	//switch (m_state)
	//{
	//case PlatGame::eState::Title:
	//	/*if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
	//	{
	//		m_state = eState::StartGame;
	//		m_scene->GetActorByName("Background");
	//	}*/
	//	break;

	//case PlatGame::eState::StartGame:
	//	
	//	break;

	//case PlatGame::eState::StartLevel:

	//	break;
	//case PlatGame::eState::Game:
	//	

	//	break;

	//case eState::PlayerDeadStart:
	//
	//	break;

	//case PlatGame::eState::PlayerDead:
	//	
	//	break;
	//case PlatGame::eState::GameOver:
	//	
	//	break;
	//default:
	//	break;
	//}

	m_scene->Update(dt);
}

void PlatGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);

	

}

void PlatGame::AddPoints(const kiko::Event& event) {
	m_score += std::get<int>(event.data);
}

void PlatGame::OnPlayerDead(const kiko::Event event)
{
	m_state = eState::PlayerDeadStart;
}
