#include <vector>
#include <random>
#include <logging/logging.h>
#include <ecs/systems/render_system.h>
#include <ecs/systems/physics_system.h>
#include <ecs/core/entity_component_system.h>
#include <ecs/components/transform.h>
#include <ecs/components/rigid_body.h>
#include <ecs/components/renderable.h>
#include <ecs/components/camera.h>
#include <ecs/components/gravity.h>
#include <ecs/utils/timer.h>

int main() {
	lLog(lInfo) << "cube example";
	auto ecs = std::make_shared<ecs::core::EntityComponentSystem>();
	auto render_window = ecs::system::RenderFactory::CreateRenderWindow(
		ecs,
		vector::Vector2D(800,600),
		"Cube Example");
	auto render_system = ecs::system::RenderFactory::CreateRenderSystem(
		ecs,
		render_window
	);

	// components
	ecs->RegisterComponent<ecs::component::Gravity>();
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
	auto physic_system = std::make_shared<ecs::system::PhysicSystem>(ecs);
	ecs->RegisterSystem<ecs::system::PhysicSystem>(physic_system);
	{
		ecs::core::Signature signature;
		signature.set(ecs->GetComponentType<ecs::component::Gravity>());
		signature.set(ecs->GetComponentType<ecs::component::RigidBody>());
		signature.set(ecs->GetComponentType<ecs::component::Transform>());
		ecs->SetSystemSignature<ecs::system::PhysicSystem>(signature);
	}

	physic_system->Init(); 
	render_system->Init(); 

	std::vector<ecs::core::Entity> entities(1000);

	std::random_device rd;
	std::mt19937 generator(rd());

	std::uniform_real_distribution<float> random_pos_x(0.0f, 780.0f);
	std::uniform_real_distribution<float> random_pos_y(0.0f, 580.0f);
	std::uniform_real_distribution<float> random_color(0, 255);

	for (auto& entity : entities) {
		entity = ecs->CreateEntity();
		
		ecs->AddComponent<ecs::component::Transform>(
			entity,
			ecs::component::Transform{ Vector{random_pos_x(generator), random_pos_y(generator)}, Vector{0,0}, Vector{0,0} });
		ecs->AddComponent<ecs::component::Renderable>(
			entity,
			ecs::component::Renderable{ 
				(uint8_t)random_color(generator),
				(uint8_t)random_color(generator),
				(uint8_t)random_color(generator) }
		);

		ecs->AddComponent<ecs::component::RigidBody>(
			entity,
			ecs::component::RigidBody{ Vector{0,0}, Vector{0,0} }
		);
		ecs->AddComponent<ecs::component::Gravity>(
			entity,
			ecs::component::Gravity{ Vector{0,1} }
		);
	}

	ecs::utils::Timer update_clock;

	const uint32_t update_rate = 1000 / 60; // 60Hz
	uint32_t update_next = update_clock.GetTime();
	uint8_t max_updates = 5;
	lLog(lInfo) << "Update rate = " << update_rate;
	try {

		while (bool running = true) {
			uint8_t updates = 0;
		
			// Process Events
			render_window->ProcessEvents();

			uint32_t update_time = update_clock.GetTime();

			while ((update_time - update_next) >= update_rate && updates++ < max_updates) {
				physic_system->Update(update_rate);
				render_system->Update(update_rate);
				update_next += update_rate;
			}
			render_system->Render();
		}
	}
	catch (const ecs::core::Exception& e) {
		lLog(lError) << e.what();
	}

	return 0;
}