#include <ecs/systems/render_system.h>

#if BACKEND_SFML
#include <ecs/systems/render_sfml.h>
#else
throw "backend not implemented"
#endif

namespace ecs::system {

	std::shared_ptr<RenderWindow> RenderFactory::CreateRenderWindow(std::shared_ptr<ecs::core::EntityComponentSystem> ecs) {
#if BACKEND_SFML
		return std::make_shared<SFMLWindow>(ecs);
#else
		throw "backend not implemented";
#endif
	}
}