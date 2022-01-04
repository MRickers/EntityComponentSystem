#include <ecs/systems/render_system.h>

#if BACKEND_SFML
#include <ecs/systems/render_sfml.h>
#else
throw "backend not implemented"
#endif

namespace ecs::system {

	std::shared_ptr<RenderWindow> RenderFactory::CreateRenderWindow(
		std::shared_ptr<ecs::core::EntityComponentSystem> ecs,
		const vector::Vector2D& size,
		const std::string& window_name) {
#if BACKEND_SFML
		return std::make_shared<ecs::system::SFMLWindow>(ecs, size, window_name);
#else
		throw "backend not implemented";
#endif
	}

	std::shared_ptr<RenderSystem> RenderFactory::CreateRenderSystem(
		std::shared_ptr<ecs::core::EntityComponentSystem> ecs,
		std::shared_ptr<RenderWindow> render_window
	) {
#if BACKEND_SFML
		return std::make_shared<ecs::system::SFMLRenderSystem>(ecs, render_window);
#else

#endif
	}
}