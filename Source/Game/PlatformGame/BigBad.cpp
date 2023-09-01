#include "BigBad.h"
#include "Framework/FrameWork.h"
namespace kiko {

	CLASS_DEFINITION(BigBad);
	bool BigBad::Initialize()
	{
		Actor::Initialize();
		return true;
	}
	void BigBad::Update(float dt)
	{
		Actor::Update(dt);


	}
	void BigBad::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "HammerTime") {
			
			destroyed = true;


		}
	}
	void BigBad::OnCollisionExit(Actor* other)
	{

	}

	void BigBad::Read(const json_t& value) {
		Actor::Read(value);

	}
	
}