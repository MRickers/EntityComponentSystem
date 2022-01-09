#pragma once
#include <vector2d.h>

namespace ecs::component {

	struct RigidBody {
		RigidBody() : velocity(0,0), acceleration(0,0) {}
		RigidBody(const Vector& vel, const Vector& acc) : velocity(vel), acceleration(acc) {}
		Vector velocity;
		Vector acceleration;
	};
}