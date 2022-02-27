#include "ecs/core/entity_manager.h"
#include "ecs/core/ecs_exception.h"

namespace ecs {
	namespace core {

		EntityManager::EntityManager(uint16_t max_entity_count) :
			available_entities_(),
			living_entities_(),
			signatures_(),
			entity_count_(0) {

			for (Entity entity = 0; entity < (max_entity_count-1 > MAX_ENTITIES ? MAX_ENTITIES : max_entity_count); entity++) {
				available_entities_.push(entity);
			}
		}

		Entity EntityManager::CreateEntity() {
			checkEntityRange(entity_count_);

			if (available_entities_.size() == 0) {
				throw Exception(
					"Max number of entities",
					static_cast<int>(ERROR::ENTITY_MAX_COUNT),
					""
				);
			}
			Entity id = available_entities_.front();
			living_entities_.insert(id);
			available_entities_.pop();
			entity_count_++;

			return id;
		}

		void EntityManager::DestroyEntity(const Entity entity) {
			checkEntityRange(entity);
			checkEntityExists(entity);

			available_entities_.push(entity);
			living_entities_.erase(entity);
			signatures_[entity].reset();

			entity_count_--;
		}

		void EntityManager::SetSignature(const Entity entity, const Signature signature) {
			checkEntityRange(entity);
			checkEntityExists(entity);

			signatures_[entity] = signature;
		}

		Signature EntityManager::GetSignature(const Entity entity) {
			checkEntityRange(entity);

			try {
				return signatures_.at(entity);
			}
			catch (const std::out_of_range& e) {
				throw Exception(
					e.what(),
					static_cast<int>(ERROR::ENTITY_OUT_OF_RANGE),
					std::string("Entity: "+entity).c_str()
				);
			}
		}

		void EntityManager::checkEntityRange(const Entity entity) const {
			if (entity > MAX_ENTITIES) {
				throw Exception(
					"Entity out if Range",
					static_cast<int>(ERROR::ENTITY_OUT_OF_RANGE),
					""
				);
			}
		}

		void EntityManager::checkEntityExists(const Entity entity) const {
			for (const auto e : living_entities_) {
				if (living_entities_.count(e)) {
					return;
				}
			}
			throw Exception(
				"Entity did not exist",
				static_cast<int>(ERROR::ENTITY_NOT_EXISTING),
				""
			);

		}
	}
}