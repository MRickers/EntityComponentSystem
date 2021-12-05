#pragma once
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "ecs/event/event.h"

namespace ecs::event {
	class EventHandler {
	private:
		typedef std::vector<std::unique_ptr< IHandlerFunction>> handlerList;

		std::unordered_map<std::type_index, handlerList> subscribers_;

	public:
		template<typename EventType>
		void Publish(const std::shared_ptr<EventType> evnt) {
			const auto handlers = subscribers_.find(typeid(EventType));

			if (handlers != subscribers_.end()) {
				for (auto& handler : handlers->second) {
					handler->Exec(evnt);
				}
			}
		}

		template<typename Instance, typename EventType>
		void Subscribe(
			std::unique_ptr<Instance> instance,
			void(Instance::* instance_callback_fn)(const std::shared_ptr<EventType> evnt) ) {
		
			auto handlers = subscribers_.find(typeid(EventType));

			if (handlers == subscribers_.end()) {
				subscribers_[typeid(EventType)] = handlerList();
				handlers = subscribers_.find(typeid(EventType));
			}

			handlers->second.push_back(std::make_unique<MemberFunctionHandler<Instance, EventType>>(std::move(instance), instance_callback_fn));
		}



	};
}