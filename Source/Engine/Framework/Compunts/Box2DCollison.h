#pragma once
#pragma once
#include "CollsionComponent.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace kiko
{
	class Box2DCollisionComponent : public CollsionComponent
	{
	public:
		using collisionFunction = std::function<void(Actor*)>;

	public:
		CLASS_DECLARTION(Box2DCollisionComponent);

		virtual bool Initialize() override;
		virtual void Update(float dt) override;

	private:
		PhysicsSystem::CollisionData data;
		vec2 scaleOffset = vec2{ 1, 1 };
	};
}
