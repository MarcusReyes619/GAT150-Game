#pragma once
#include "Component.h"

namespace kiko {
	class RenderComponent : public  Component {
	public:
		virtual void Draw(class Renderer& render) = 0;


	protected:



	};
	

}
