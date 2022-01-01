#pragma once
#include <vector2d.h>

namespace ecs::component {

	struct RigidBody {
		Vector velocity;
		Vector acceleration;
	};
}