namespace ecs {
	namespace core {

		template<typename T>
		void ComponentArray<T>::Insert(const Entity entity, T component) {
			try {
				const std::size_t new_index = size_;
				entity_to_index_[entity] = new_index;
				index_to_entity_[new_index] = entity;
				component_array_.at(new_index) = component;
				size_++;
			} catch(const std::out_of_range& e) {
				throw Exception(
						e.what(),
						static_cast<int>(ERROR::COMPONENT_MAX_COUNT),
						""
					);
			}
		}

		template<typename T>
		void ComponentArray<T>::remove(const Entity entity) {
			try {
				std::size_t index_of_removed_entity = entity_to_index_.at(entity);
				std::size_t index_of_last_entity = size_ - 1;
				component_array_.at(index_of_removed_entity) = component_array_.at(index_of_last_entity);

				Entity last_entity = index_to_entity_.at(index_of_last_entity);
				entity_to_index_.at(last_entity) = index_of_removed_entity;
				index_to_entity_.at(index_of_removed_entity) = last_entity;

				entity_to_index_.erase(entity);
				index_to_entity_.erase(index_of_last_entity);

				size_--;
			} catch(const std::out_of_range& e) {
				throw Exception(
					e.what(),
					static_cast<int>(ERROR::COMPONENT_INDEX_ERROR),
					""
				);
			}
		}

		template<typename T>
		T& ComponentArray<T>::Get(const Entity entity) {
			try {
				const auto index = entity_to_index_.at(entity);
				return component_array_.at(index);

			} catch(const std::out_of_range& e) {
				throw Exception(
					e.what(),
					static_cast<int>(ERROR::COMPONENT_INDEX_ERROR),
					""
				);
			}
		}

		template<typename T>
		void ComponentArray<T>::Remove(const Entity entity) {
			remove(entity);
		}

		template<typename T>
		void ComponentArray<T>::DestroyEntity(const Entity entity) {
			remove(entity);
		}
	}
}