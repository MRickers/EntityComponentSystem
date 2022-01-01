#pragma once
#include <vector2d.h>

namespace ecs::component {

	struct Transform {
		Transform() : position(0,0), rotation(0,0), scale(0,0) {}
		Transform(const Vector& pos, const Vector& rot, const Vector& scle) :
			position(pos), rotation(rot), scale(scle){}
		Vector position;
		Vector rotation;
		Vector scale;
	};
}