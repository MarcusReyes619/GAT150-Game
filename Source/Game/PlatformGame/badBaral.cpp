#include "badBaral.h"

namespace kiko {

	CLASS_DEFINITION(BadBaral);


	bool kiko::BadBaral::Initialize() {
		Actor::Initialize();

		m_physicsComp = GetComponent<kiko::PhyicsComponent>();

	
		return true;
	}

	void kiko::BadBaral::OnDestroy() {
	
		

	}

	void kiko::BadBaral::Update(float dt) {
		Actor::Update(dt);
		
		if (!m_physicsComp)return;
		kiko::vec2 forward = kiko::vec2{ 1, 0 };

		m_physicsComp->ApplyForce(forward * speed * dir);


	}

	void kiko::BadBaral::OnCollisionEnter(Actor* other) {

		if (other->tag == "HammerTime") {

			destroyed = true;


		}
		if (other->tag == "Ground")dir = -1;
		if (other->tag == "Ground2")dir = 1;
	}
	void BadBaral::Read(const json_t& value) {
		Actor::Read(value);

	}


}