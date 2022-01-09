#pragma once
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"

namespace ecs {
	namespace core {

		class EntityComponentSystem {
		private:
			std::shared_ptr<EntityManager> entity_manager_;
			std::shared_ptr<ComponentManager> component_manager_;
			std::shared_ptr<SystemManager> system_manager_;

		public:
			EntityComponentSystem(
				std::shared_ptr<EntityManager> entity_manager = std::make_shared<EntityManager>(),
				std::shared_ptr<ComponentManager> component_manager = std::make_shared<ComponentManager>(),
				std::shared_ptr<SystemManager> system_manager = std::make_shared<SystemManager>()) :
				entity_manager_(entity_manager),
				component_manager_(component_manager),
				system_manager_(system_manager) {

			}

			Entity CreateEntity() {
				return entity_manager_->CreateEntity();
			}

			void DestroyEntity(const Entity entity) {
				entity_manager_->DestroyEntity(entity);
				component_manager_->DestroyEntity(entity);
				system_manager_->DestroyEntity(entity);
			}

			// Component Methods
			template<typename T>
			void RegisterComponent() {
				component_manager_->RegisterComponent<T>();
			}

			template<typename T>
			void AddComponent(const Entity entity, T component) {
				component_manager_->AddComponent<T>(entity, component);

				Signature signature = entity_manager_->GetSignature(entity);
				signature.set(component_manager_->GetComponentType<T>(), true);
				entity_manager_->SetSignature(entity, signature);
				system_manager_->SetEntitySignature(entity, signature);
			}

			template<typename T>
			void RemoveComponent(const Entity entity) {
				component_manager_->RemoveComponent<T>(entity);

				Signature signature = entity_manager_->GetSignature(entity);
				signature.set(component_manager_->GetComponentType<T>(), false);
				entity_manager_->SetSignature(entity, signature);
				system_manager_->SetEntitySignature(entity, signature);
			}

			template<typename T>
			T& GetComponent(const Entity entity) {
				return component_manager_->GetComponent<T>(entity);
			}

			template<typename T>
			ComponentType GetComponentType() {
				return component_manager_->GetComponentType<T>();
			}

			// System Methods

			template<typename T>
			void RegisterSystem(std::shared_ptr<ecs::core::System> system) {
				system_manager_->RegisterSystem<T>(system);
				system_manager_->SetSignature<T>(ecs::core::Signature{});
			}

			template<typename T>
			std::shared_ptr<T> RegisterSystem() {
				auto system = system_manager_->RegisterSystem<T>();
				system_manager_->SetSignature<T>(ecs::core::Signature{});
				return system;
			}

			template<typename T>
			void SetSystemSignature(const Signature signature) {
				system_manager_->SetSignature<T>(signature);
			}
		};
	}
}