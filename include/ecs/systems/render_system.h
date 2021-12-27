#pragma once
#include <memory>
#include <ecs/systems/render_system_interface.h>
#include <ecs/core/entity_component_system.h>

namespace ecs::system {
	class RenderFactory {
		static std::shared_ptr<RenderWindow> CreateRenderWindow(std::shared_ptr<ecs::core::EntityComponentSystem> ecs);
	};
}