#include "Event.h"
#include "Framework/Singleton.h"
#include <map>
#include <list>
#include <functional>

#define EVENT_SUBSCRIBE(id, function)    kiko::EventManager::Instance().Subscribe(id, this, std::bind(&function, this, std::placeholders::_1));
#define EVENT_UNSUBSCRIBE(id)            kiko::EventManager::Instance().Unsubscribe(id, this);

namespace kiko{

	

	class EventManger : public Singleton<EventManger> {

	public:
		using EventFunction = std::function<void(const Event&)>;

		struct EventDispatcher {

			IEventListener* Listener = nullptr; //object that can listien for Events
			EventFunction function;// function that is called on event
		};


		friend class Singleton;

		void Update(float dt);

		void Subscribe(Event::id_t id, IEventListener* listener, EventFunction function);
		void Unsubscribe(Event::id_t id, IEventListener* listener);

		void DispatchEvent(Event::id_t id, Event::data_t data, void* sender = nullptr, float time = 0);

	private:
		EventManger() = default;

		std::map<Event::id_t, std::list<EventDispatcher>> m_dispatch;

	};




}