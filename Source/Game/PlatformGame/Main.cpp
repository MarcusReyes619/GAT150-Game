#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/FrameWork.h"
#include "PlatGame.h"
#include "Physics/PhysicsSystem.h"
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <functional>


using namespace std;



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

	//MAIN CODE




	INFO_LOG("Initialize Engine");

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("Assets");



	// initialize engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();


	// create game
	unique_ptr<PlatGame> game = make_unique<PlatGame>();
	game->Initialize();





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

		 //update game
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		game->Draw(kiko::g_renderer);

		


		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}


	return 0;
}