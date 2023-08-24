#include "ModelRenderCompents.h"
#include "Framework/Actor.h"
#include "Framework/ResourceManager.h"

namespace kiko{

	CLASS_DEFINITION(ModelRenderComponent)

		bool ModelRenderComponent::Initialize()
	{
		if(!modelName.empty()) m_model = GET_RESOURCE(Model, modelName);
		return true;
	}

	void ModelRenderComponent::Update(float dt) {

	}
	void ModelRenderComponent::Draw(Renderer& ren)
	{
		m_model->Draw(ren,m_owner->transform);
	}

	void ModelRenderComponent::Read(const json_t& value) {
		READ_DATA(value, modelName);
	}


}


