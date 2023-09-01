#include "badBaral.h"

namespace kiko {
	bool kiko::BadBaral::Initialize() {

		return false;
	}

	void kiko::BadBaral::OnDestroy() {
		

	}

	void kiko::BadBaral::Update(float dt) {

	}

	void kiko::BadBaral::OnCollisionEnter(Actor* other) {

		if (other->tag == "PlayerHamer") {
			//OnDestroy();
			destroyed = true;
		}
	}

}