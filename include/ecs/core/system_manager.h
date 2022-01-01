#pragma once
#include "entity_manager.h"
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <set>
#include <memory>

namespace ecs {
	namespace core {

		class System {
		public:
			virtual ~System() {}
			std::set<Entity> entities_;
		};

		class SystemManager {
		private:
			std::unordered_map<std::string, Signature> signatures_;
			std::unordered_map<std::string, std::shared_ptr<System>> systems_;
		public:
			template<typename T>
			void RegisterSystem(std::shared_ptr<System> system) {
				const auto type_name = typeid(T).name();

				if (systems_.insert({ type_name, system }).second == false) {
					throw Exception(
						std::string("System already exist").c_str(),
						__FILE__,
						__LINE__,
						static_cast<int>(ERROR::SYSTEM_ALREADY_REGISTERED),
						""
					);
				}
			}

			template<typename T>
			std::shared_ptr<T> RegisterSystem() {
				const auto type_name = typeid(T).name();

				try {
					auto system = std::make_shared<T>();

					if (systems_.insert({ type_name, system }).second == false) {
						throw Exception(
							std::string("System already exist").c_str(),
							__FILE__,
							__LINE__,
							static_cast<int>(ERROR::SYSTEM_ALREADY_REGISTERED),
							""
						);
					}
					return system;
				}
				catch (const std::bad_alloc& e) {
					throw Exception(
						e.what(),
						__FILE__,
						__LINE__,
						static_cast<int>(ERROR::SYSTEM_OUT_OF_MEMORY),
						""
					);
				}
			}

			template<typename T>
			void SetSignature(Signature signature) {
				const auto type_name = typeid(T).name();

				signatures_.insert_or_assign(type_name, signature);
			}

			void SetEntitySignature(const Entity entity, const Signature entity_signature) {
				try {
					for (const auto& systems : systems_) {
						const auto& type = systems.first;
						const auto& system = systems.second;
						const auto& system_signature = signatures_.at(type);

						if ((entity_signature & system_signature) == system_signature) {
							system->entities_.insert(entity);
						}
						else {
							system->entities_.erase(entity);
						}
					}
				}
				catch (const std::out_of_range& e) {
					throw Exception(
						e.what(),
						__FILE__,
						__LINE__,
						static_cast<int>(ERROR::SYSTEM_SIGNATURE_NOT_FOUND),
						""
					);
				}
			}

			void DestroyEntity(const Entity entity) {
				for (const auto& systems : systems_) {
					const auto& system = systems.second;

					system->entities_.erase(entity);
				}
			}
		};
	}
}