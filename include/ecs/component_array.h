#pragma once
#include "entity_manager.h"
#include <unordered_map>

namespace ecs {
	template<typename T>
	class ComponentArray {
	private:
		std::array<T, MAX_ENTITIES> component_array_;
		std::unordered_map<Entity, std::size_t> entity_to_index_;
		std::unordered_map<std::size_t, Entity> index_to_entity_;
		std::size_t size_;
	public:
		ComponentArray() : component_array_(), entity_to_index_(), index_to_entity_(), size_(0) {}

		void Insert(const Entity entity, T component);
		void Remove(const Entity entity);
		//T& Get(const Entity entity) const;
		//void DestroyEntity(const Entity entity);
	};
}

#include "component_array.tpl"