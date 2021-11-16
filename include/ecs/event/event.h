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
		virtual void Exec(std::unique_ptr<IEvent> evnt) = 0;
	};

	template<typename Instance, typename EventType>
	class MemberFunctionHandler : public IHandlerFunction {
	private:
		typedef void (Instance::*callback)(const std::unique_ptr<EventType>&);
		std::unique_ptr<Instance> instance_;
		callback callback_;
	public:
		MemberFunctionHandler(std::unique_ptr<Instance> instance, callback handler_function) :
			instance_{ std::move(instance) },
			callback_{ handler_function }
		{}

		void Exec(std::unique_ptr<IEvent> evnt) override {
			auto deleter = evnt.get_deleter();
			auto derived_ptr = static_cast<EventType*>(evnt.release());
			auto derived_uptr = std::unique_ptr<EventType>(derived_ptr);
			((instance_.get())->*callback_)(derived_uptr);
		}
	};
}