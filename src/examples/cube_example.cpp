#include <logging/logging.h>
#include <ecs/systems/render_system.h>
#include <ecs/core/entity_component_system.h>

int main() {
	lLog(lInfo) << "cube example";
	auto ecs = std::make_shared<ecs::core::EntityComponentSystem>();
	try {
		auto render_window = ecs::system::RenderFactory::CreateRenderWindow(
			ecs,
			vector::Vector2D(800,600),
			"Test");
	}
	catch (const std::bad_alloc& e) {
		lLog(lError) << e.what();
	}

	return 0;
}