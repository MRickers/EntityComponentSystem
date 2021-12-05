#pragma once
#include <memory>
#include <functional>

namespace ecs::event {
	// data
	class IEvent {
	public:
		virtual ~IEvent() {}
	};

	// logic
	class IHandlerFunction {
	public:
		virtual ~IHandlerFunction() {}
		virtual void Exec(const std::shared_ptr<IEvent> evnt) = 0;
	};

	template<typename Instance, typename EventType>
	class MemberFunctionHandler : public IHandlerFunction {
	private:
		typedef void (Instance::*callback)(const std::shared_ptr<EventType>);
		std::unique_ptr<Instance> instance_;
		callback callback_;
	public:
		MemberFunctionHandler(std::unique_ptr<Instance> instance, callback handler_function) :
			instance_{ std::move(instance) },
			callback_{ handler_function }
		{}

		void Exec(const std::shared_ptr<IEvent> evnt) override {
			const auto casted_ptr = std::static_pointer_cast<EventType>(evnt);
			((instance_.get())->*callback_)(casted_ptr);
		}
	};
}