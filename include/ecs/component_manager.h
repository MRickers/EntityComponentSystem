#pragma once
#include "component_array.h"
#include <memory>
#include <typeinfo>

namespace ecs {
	class ComponentManager {
	private:

		std::unordered_map<std::string, std::shared_ptr<IComponentArray>> components_;

		template<typename T>
		std::shared_ptr<ComponentArray<T>> getComponent() {
			const auto type_name = typeid(T).name();

			try {
				return std::static_pointer_cast<ComponentArray<T>>(components_.at(type_name));
			}
			catch (const std::out_of_range& e) {
				throw Exception(
					e.what(),
					__FILE__,
					__LINE__,
					static_cast<int>(ERROR::COMPONENT_TYPE_NOT_FOUND),
					""
				);
			}
		}
	public:
		
		template<typename T>
		void RegisterComponent() noexcept {
			const auto type_name = typeid(T).name();

			components_.insert({ type_name, std::make_shared<ComponentArray<T>>() });
		}

		template<typename T>
		void AddComponent(const Entity entity, const T component) {
			getComponent<T>()->Insert(entity, component);			
		}

		template<typename T>
		T& GetComponent(const Entity entity) {
			return getComponent<T>()->Get(entity);
		}

		void DestroyEntity(const Entity entity) {
			for (const auto& components : components_) {
				const auto& component = components.second;

				component->DestroyEntity(entity);
			}
		}
	};
}