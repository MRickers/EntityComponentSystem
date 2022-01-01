#pragma once
#include <vector2d.h>
#include <ecs/components/transform.h>

namespace ecs::component {

	struct Camera {
		Camera() : size(0,0), transform() {}
		Vector size;
		Transform transform;
	};
}