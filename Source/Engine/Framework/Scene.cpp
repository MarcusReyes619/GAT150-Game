#include "Scene.h"
#include "Framework/Compunts/CollsionComponent.h"

namespace kiko
{
	bool Scene::Initialize()
	{
		for (auto& actor : m_actors) actor->Initialize();

		return true;
	}
	void Scene::Update(float dt)
	{
		// update and remove destroyed actors
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(*iter)->Update(dt);
			iter = ((*iter)->destroyed) ? m_actors.erase(iter) : ++iter;
		}

		// check collisions
		/*
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++)
		{
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++)
			{
				CollsionComponent* collision1 = (*iter1)->GetComponent<CollsionComponent>();
				CollsionComponent* collision2 = (*iter2)->GetComponent<CollsionComponent>();


				if (!collision1|| collision2 == nullptr)continue;

				if (collision1->CheckCollision(collision2))
				{
					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}
			}
		}
		*/
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors) {

			if (actor->active) actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		if (!actor) return;
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll(bool force)
	{
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{

			(force || !(*iter)->persistent) ? iter = m_actors.erase(iter) : iter++;
		}
		//m_actors.clear();
	}

	bool Scene::Load(const std::string& filename)
	{
		rapidjson::Document doc;

		if (!Json::Load(filename, doc)) {
			ERROR_LOG("Could not load scene file: " << filename);
			return false;
		}
		Read(doc);

		return true;
	}

	void Scene::Read(const json_t& value)
	{


		if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
		{
			for (auto& actorValue : GET_DATA(value, actors).GetArray())
			{
				std::string type;
				READ_DATA(actorValue, type);

				auto actor = CREATE_CLASS_BASE(Actor, type);

				if (!actor) return;

				actor->Read(actorValue);

				if (actor->prototype) {
					std::string name = actor->name;
					Factory::Instance().RegisterPrototype(name, std::move(actor));
				}
				else {

					Add(std::move(actor));

				}

			}
		}
	}

}