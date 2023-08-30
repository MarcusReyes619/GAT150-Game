#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/FrameWork.h"

namespace kiko {


    CLASS_DEFINITION(Weapon);

    bool Weapon::Initialize()
    {
        Actor::Initialize();

        m_physicComp = GetComponent<PhyicsComponent>();

        auto collisionComponent = GetComponent<kiko::CollsionComponent>();
            if (collisionComponent)
            {
              
            }

        return true;
    }


    void Weapon::Update(float dt)
    {
        Actor::Update(dt);

        kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
       m_physicComp->SetVelocity(forward * speed);

        transform.position += forward * speed * kiko::g_time.GetDeltaTime();
        transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
        transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

    }

    void Weapon::OnCollisionEnter(Actor* other)
    {
        if (other->tag != tag)
        {
            destroyed = true;
        }
    }

    void Weapon::Read(const json_t& value)
    {
        Actor::Read(value);

        READ_DATA(value, speed);
    }
} 