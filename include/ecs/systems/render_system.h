#pragma once
#include <memory>
#include <ecs/systems/render_system_interface.h>
#include <ecs/core/entity_component_system.h>

namespace ecs::system {
	class RenderFactory {
	public:
		static std::shared_ptr<RenderWindow> CreateRenderWindow(
			std::shared_ptr<ecs::core::EntityComponentSystem> ecs,
			const vector::Vector2D& size,
			const std::string& window_name);

		static std::shared_ptr<RenderSystem>CreateRenderSystem(
			std::shared_ptr<ecs::core::EntityComponentSystem> ecs,
			std::shared_ptr<RenderWindow> render_window);
	};
}