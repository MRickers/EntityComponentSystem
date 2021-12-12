#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include <typeindex>
#include <any>
#include <optional>

namespace ecs::event {
	using EventId = std::uint32_t;

	class Event {
	private:
		std::any data_;
		EventId id_;
	public:
		Event() = delete;

		Event(EventId id) : data_(), id_(id) {}

		template<typename T>
		Event(const T& data, EventId id) : data_(data), id_(id){}

		template<typename T>
		T GetData() const {
			return std::any_cast<T>(data_);
		}

		template<typename T>
		void SetData(const T& data) {
			data_ = data;
		}

		EventId GetId() const {
			return id_;
		}
	};

	class EventHandler {
		typedef std::vector<std::function<void(const Event&)>> handlerArray;
	private:
		std::unordered_map<EventId, handlerArray> listeners_;
	public:
		
		void Subscribe(EventId id, std::function<void(const Event&)> callback) {
			if (auto listener = listeners_.find(id); listener == listeners_.end()) {
				handlerArray handler;
				handler.push_back(callback);
				listeners_[id] = handler;
			}
			else {
				listener->second.push_back(callback);
			} 
		}

		void Publish(const Event& evnt) {
			const auto id = evnt.GetId();

			for (const auto& listener : listeners_.at(id)) {
				listener(evnt);
			}
		}

		void Publish(EventId id) {
			Event evnt{ id };

			Publish(evnt);
		}
	};
}