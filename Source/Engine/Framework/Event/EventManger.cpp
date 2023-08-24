#include "EventManger.h"
#include "Core/Logger.h"

void kiko::EventManger::Update(float dt){

}

void kiko::EventManger::Subscribe(Event::id_t id, IEventListener* listener, EventFunction function){

	EventDispatcher dispatch;

	dispatch.Listener = listener;
	dispatch.function = function;

	INFO_LOG("Event subscrided" << id);

	m_dispatch[id].push_back(dispatch);
	

}

void kiko::EventManger::Unsubscribe(Event::id_t id, IEventListener* listener){

}

void kiko::EventManger::DispatchEvent(Event::id_t id, Event::data_t data, void* sender, float time){

	Event event{ id, data };

	if (m_dispatch.find(id) != m_dispatch.end()) {
		auto& dispatchers = m_dispatch[id];
		for (auto& dispatcher : dispatchers) {
			
			dispatcher.function(event);
		}
	}

}
