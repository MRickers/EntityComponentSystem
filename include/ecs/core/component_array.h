#pragma once
#include "entity_manager.h"
#include <unordered_map>

namespace ecs {
	namespace core {

		class IComponentArray {
		public:
			virtual ~IComponentArray() = default;
			virtual void DestroyEntity(const Entity entity) = 0;
		};

		template<typename T>
		class ComponentArray : public IComponentArray{
		private:
			std::array<T, MAX_ENTITIES> component_array_;
			std::unordered_map<Entity, std::size_t> entity_to_index_;
			std::unordered_map<std::size_t, Entity> index_to_entity_;
			std::size_t size_;

			void remove(const Entity entity);
		public:
			ComponentArray() : component_array_(), entity_to_index_(), index_to_entity_(), size_(0) {}

			void Insert(const Entity entity, T component);
			T& Get(const Entity entity);
			void Remove(const Entity entity);
			void DestroyEntity(const Entity entity) override;
		};
	}
}

#include "component_array.tpl"