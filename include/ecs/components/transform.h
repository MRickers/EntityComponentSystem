#include <vector2d.h>

namespace ecs::component {
	using Vec = vector::Vector2D;

	struct Transform {
		Vec position;
		Vec rotation;
		Vec scale;
	};
}