#include <ecs/systems/physics_system.h>
#include <ecs/components/gravity.h>
#include <ecs/components/rigid_body.h>
#include <ecs/components/transform.h>

namespace ecs::system {

	PhysicSystem::PhysicSystem(std::shared_ptr<ecs::core::EntityComponentSystem> ecs) : ecs_(ecs) {}

	void PhysicSystem::Init() {

	}

	void PhysicSystem::Update(uint32_t dt) {
		for (const auto& entity : entities_) {
			auto& transform = ecs_->GetComponent<ecs::component::Transform>(entity);
			auto& rigidbody = ecs_->GetComponent<ecs::component::RigidBody>(entity);
			const auto& gravity = ecs_->GetComponent<ecs::component::Gravity>(entity);

			transform.position += rigidbody.velocity * dt;
			rigidbody.velocity += gravity.force * dt;
			rigidbody.velocity.SetLimit(0.01); // uppper bound for velocity
		}
	}
}