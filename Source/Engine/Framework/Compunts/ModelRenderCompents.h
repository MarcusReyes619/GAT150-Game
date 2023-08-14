#include "RenderCompunts.h"
#include "Renderer/Model.h"

namespace kiko {
	class ModelRenderComponent : public RenderComponent {
	public:
		void Update(float dt)override;
		void Draw(class Renderer& ren)override;

		virtual float GetRadius()override { return m_model->GetRadius(); } 

	public:
		res_t<Model>m_model;
	};
}