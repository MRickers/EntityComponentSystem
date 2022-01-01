#pragma once
#include <vector2d.h>

namespace ecs::component {

	struct Transform {
		Vector position;
		Vector rotation;
		Vector scale;
	};
}