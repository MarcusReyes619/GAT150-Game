#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/FrameWork.h"
#include "Player.h"
#include "Enemy.h"
#include "SpaceGame.h"
#include "Physics/PhysicsSystem.h"
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <functional>


using namespace std;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};

//template <typename T>
//void print(const std::string& s, const T& container)
//{
//	std::cout << s << std::endl;
//		for (auto element : container)
//		{
//			std::cout << element << " ";
//		}
//	std::cout << std::endl;
//}
void print_arg(int count, ...)
{
	va_list args;



	va_start(args, count);
	for (int i = 0; i < count; ++i)
	{
		std::cout << va_arg(args, const char*) << std::endl;
	}
	va_end(args);
}

void zero(int i) {
	i = 0;
}

void print(int i) {
	cout << i << endl;
}


int sub(int i, int z) {
	return i - z;
}

class A {
public:
	int add(int i, int z) {
		return i + z;
	}

};

union Data {
	int i; 
	bool b;
	char c[6];


};


//JOSON ASSIMENT
/*rapidjson::Document document;
	kiko::Json::Load("json.txt", document);
	int i1;
	kiko::Json::Read(document, "integer1", i1);
	std::cout << i1 << std::endl;
	int i2;
	kiko::Json::Read(document, "integer2", i2);
	std::cout << i2 << std::endl;

	std::string str;
	kiko::Json::Read(document,"string",str);
		std::cout << str << std::endl;
	bool b;
	kiko::Json::Read(document, "boolean", b);
	std::cout << b << std::endl;
	float f;
	kiko::Json::Read(document, "float", f);

		std::cout << f << std::endl;
	kiko::vec2 v2;
	kiko::Json::Read(document, "vector2", v2);

		std::cout << v2 << std::endl;*/


int main(int argc, char* argv[])
{
	//Data data;
	//data.b  = true;
	//cout << data.b << endl;

	//void(*func_ptr)(int) = &print;
	//func_ptr(5);


	//int(*op_ptr)(int, int);
	//op_ptr = sub;


	//cout << op_ptr(4, 4) << endl;

	//std::function<int(int, int)>op;
	////op = add;
	////cout << op(1, 2) << endl;

	//A a;
	//op = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);
	//cout << op(6, 6) << endl;


	//MAIN CODE

	


	INFO_LOG("Initialize Engine");

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	

	// initialize engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();


	// create game
	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	// main game loop
	bool quit = false;
	while (!quit)
	{
		// update engine
	kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		// update game
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		game->Draw(kiko::g_renderer);

		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());
			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			star.Draw(kiko::g_renderer);
		}

	//kiko::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		kiko::g_particleSystem.Draw(kiko::g_renderer);
		
		kiko::g_renderer.EndFrame();
	}

	stars.clear();

	return 0;
}
/*
		if (kiko::g_inputSystem.GetMouseButtonDown(0) &&
			!kiko::g_inputSystem.GetPreviousMouseButtonDown(0))
		{
			kiko::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = kiko::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;

			data.color = kiko::Color{ 1, 1, 1, 1 };

			kiko::Transform transform{ { kiko::g_inputSystem.GetMousePosition() }, 0, 1};
			auto emitter = std::make_unique<kiko::Emitter>(transform, data);
			emitter->m_lifespan = 1.0f;
			scene.Add(std::move(emitter));
		}
*/