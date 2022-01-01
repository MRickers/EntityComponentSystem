#include <logging/logging.h>
#include <ecs/systems/render_system.h>
#include <ecs/core/entity_component_system.h>
#include <ecs/components/transform.h>
#include <ecs/components/rigid_body.h>
#include <ecs/components/renderable.h>

int main() {
	lLog(lInfo) << "cube example";
	auto ecs = std::make_shared<ecs::core::EntityComponentSystem>();
	auto render_window = ecs::system::RenderFactory::CreateRenderWindow(
		ecs,
		vector::Vector2D(800,600),
		"Test");

	ecs->RegisterComponent<ecs::component::Transform>();

	return 0;
}