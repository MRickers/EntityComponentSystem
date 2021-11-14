#pragma once
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <event.h>
#include <memory>

namespace ecs::event {
	class EventHandler {
	private:
		std::unordered_map<std::type_info, std::unique_ptr< IHandlerFunction>> handlers_;
	public:
		void HandleEvents(const std::unique_ptr<IEvent>& event) const;

	};
}