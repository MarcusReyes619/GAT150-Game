
#include "Hammer.h"

#include "Framework/FrameWork.h"

namespace kiko {

	CLASS_DEFINITION(Hammer);

	bool Hammer::Initialize() {
		Actor::Initialize();


		m_physicsComp = GetComponent<kiko::PhyicsComponent>();
	//	m_spriteAnimationComp = GetComponent<AnimationComponet>();
		//m_spriteAnimationComp = GetComponent<SpriteComponent>();


		return true;
	}

	void Hammer::Update(float dt) {

	}

	void Hammer::OnCollisionEnter(Actor* other) {

		if (other->tag == "Player") {
			//Actor::OnDestroy();
			destroyed = true;
			std::cout << "REE";
		}
	}

	void Hammer::OnCollisionExit(Actor* other) {
	}

	void Hammer::Read(const json_t& value) {
		Actor::Read(value);

	}
	


}
