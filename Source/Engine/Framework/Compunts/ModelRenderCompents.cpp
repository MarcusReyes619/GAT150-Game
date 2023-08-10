#include "ModelRenderCompents.h"
#include "Framework/Actor.h"

namespace kiko{


	void ModelRenderComponent::Update(float dt) {

	}
	void ModelRenderComponent::Draw(Renderer& ren)
	{
		m_model->Draw(ren,m_owner->m_transform);
	}


}


