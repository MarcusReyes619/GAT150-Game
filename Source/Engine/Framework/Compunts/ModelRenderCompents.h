#include "RenderCompunts.h"
#include "Renderer/Model.h"

namespace kiko {
	class ModelRenderComponent : public RenderComponent {
	public:
		void Update(float dt)override;
		void Draw(class Renderer& ren)override;

	public:
		res_t<Model>m_model;
	};
}