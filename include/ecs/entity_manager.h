#pragma once
#include <queue>
#include <unordered_set>
#include <bitset>
#include <array>
#include "ecs/ecs_exception.h"

namespace ecs {
	inline const std::uint16_t MAX_ENTITIES = 512;
	inline const std::uint16_t MAX_COMPONENTS = 32;

	using Entity = std::uint16_t;
	using Signature = std::bitset<MAX_COMPONENTS>;

	class EntityManager {
	private:
		// unused entities
		std::queue<Entity> available_entities_;
		// remember created entities
		std::unordered_set<Entity> living_entities_;
		// array of signatures
		std::array<Signature, MAX_ENTITIES> signatures_;
		// total entities
		uint32_t entity_count_;
		
		void checkEntityRange(const Entity entity, int line) const;
		void checkEntityExists(const Entity entity, int line) const;
	public:
		EntityManager(uint16_t max_entity_count = MAX_ENTITIES);
		EntityManager(const EntityManager&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;

		Entity CreateEntity();
		void DestroyEntity(const Entity entity);
		void SetSignature(const Entity entity, const Signature signature);
		Signature GetSignature(const Entity entity);
	};
}