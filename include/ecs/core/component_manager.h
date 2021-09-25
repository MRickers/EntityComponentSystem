#pragma once
#include "component_array.h"
#include <memory>
#include <typeinfo>

namespace ecs {
	namespace core {

		using ComponentType = std::uint8_t;
		class ComponentManager {
		private:

			std::unordered_map<std::string, std::shared_ptr<IComponentArray>> components_{};
			std::unordered_map<std::string, ComponentType> component_types_{};
			ComponentType component_type_counter{};

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

				if (component_types_.find(type_name) != component_types_.end()) {
					throw Exception(
						"ComponentType already registered",
						__FILE__,
						__LINE__,
						static_cast<int>(ERROR::COMPONENT_TYPE_ALREADY_REGISTERED),
						""
					);
				}

				components_.insert({ type_name, std::make_shared<ComponentArray<T>>() });
				component_types_.insert({ type_name, component_type_counter });
				component_type_counter++;
			}

			template<typename T>
			ComponentType GetComponentType() const {
				const auto type_name = typeid(T).name();

				try {
					return component_types_.at(type_name);
				}
				catch (const std::out_of_range& e) {
					throw Exception(
						e.what(),
						__FILE__,
						__LINE__,
						static_cast<int>(ERROR::COMPONENT_TYPE_ALREADY_REGISTERED),
						""
					);
				}
			}

			template<typename T>
			void AddComponent(const Entity entity, const T component) {
				getComponent<T>()->Insert(entity, component);			
			}

			template<typename T>
			T& GetComponent(const Entity entity) {
				return getComponent<T>()->Get(entity);
			}

			template<typename T>
			void RemoveComponent(const Entity entity) {
				getComponent<T>()->Remove(entity);
			}

			void DestroyEntity(const Entity entity) {
				for (const auto& components : components_) {
					const auto& component = components.second;

					component->DestroyEntity(entity);
				}
			}
		};
	}
}