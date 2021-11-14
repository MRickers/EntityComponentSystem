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
		virtual void Exec(const std::unique_ptr<IEvent> evnt) const = 0;
	};

	template<typename Instance, typename EventType>
	class MemberFunctionHandler : public IHandlerFunction {
	private:
		std::unique_ptr<Instance> instance_;
		typedef std::function<void(std::unique_ptr<IEvent>& evnt)> callback;
		callback callback_;
	public:
		MemberFunctionHandler(std::unique_ptr<Instance> instance, callback handler_function) : 
			instance_(std::move(instance)),
			callback_(handler_function)
		{}

		void Exec(std::unique_ptr<IEvent>& evnt) const override {

		}
	};
	/*
	template<typename Instance, typename EventType>
	class MemberFunctionHandler : public IHandlerFunction {
	private:
		typedef std::function<void(const std::unique_ptr<EventType>)> callback;
		std::unique_ptr<Instance> instance_;
		callback callback_;
	public:
		MemberFunctionHandler(std::unique_ptr<Instance> instance, callback handler_function) :
			instance_(instance),
			callback_(handler_function) {}
			
		void Exec(const std::unique_ptr<IEvent> evnt) const override {
			callback_(static_cast<EventType>(evnt));
		}
	};
	*/
}