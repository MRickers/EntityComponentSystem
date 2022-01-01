#include <vector>
#include <logging/logging.h>
#include <ecs/systems/render_system.h>
#include <ecs/core/entity_component_system.h>
#include <ecs/components/transform.h>
#include <ecs/components/rigid_body.h>
#include <ecs/components/renderable.h>
#include <ecs/components/camera.h>

int main() {
	lLog(lInfo) << "cube example";
	auto ecs = std::make_shared<ecs::core::EntityComponentSystem>();
	auto render_window = ecs::system::RenderFactory::CreateRenderWindow(
		ecs,
		vector::Vector2D(800,600),
		"Cube Example");
	auto render_system = ecs::system::RenderFactory::CreateRenderSystem(
		ecs
	);

	// components
	ecs->RegisterComponent<ecs::component::Transform>();
	ecs->RegisterComponent<ecs::component::Renderable>();
	ecs->RegisterComponent<ecs::component::RigidBody>();
	ecs->RegisterComponent<ecs::component::Camera>();

	// systems
	ecs->RegisterSystem<ecs::system::RenderSystem>(render_system);
	{
		ecs::core::Signature signature;
		signature.set(ecs->GetComponentType<ecs::component::Renderable>());
		signature.set(ecs->GetComponentType<ecs::component::Transform>());
		ecs->SetSystemSignature<ecs::system::RenderSystem>(signature);
	}

	render_system->Init();

	std::vector<ecs::core::Entity> entities(1);

	for (auto& entity : entities) {
		entity = ecs->CreateEntity();
		
		ecs->AddComponent<ecs::component::Transform>(
			entity,
			ecs::component::Transform{ Vector{300, 300}, Vector{0,0}, Vector{0,0} });
	}

	return 0;
}