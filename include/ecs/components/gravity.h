#pragma once
#include <vector2d.h>

namespace ecs::component {
	struct Gravity {
		Gravity() : force(0,0) {}
		Gravity(const Vector& gravity_force) : force(gravity_force) {}
		Vector force;
	};
}