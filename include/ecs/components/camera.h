#pragma once
#include <vector2d.h>
#include <ecs/components/transform.h>

namespace ecs::component {

	struct Camera {
		Vector size;
		Transform transform;
	};
}