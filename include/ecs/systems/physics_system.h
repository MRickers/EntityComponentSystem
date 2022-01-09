#pragma once
#include <ecs/core/system_manager.h>
#include <ecs/core/entity_component_system.h>

namespace ecs::system {
	class PhysicSystem : public ecs::core::System {
	private:
		std::shared_ptr<ecs::core::EntityComponentSystem> ecs_;
	public:
		PhysicSystem(std::shared_ptr<ecs::core::EntityComponentSystem> ecs);
		virtual ~PhysicSystem() {}
		void Init();
		void Update(uint32_t dt);
	};
}