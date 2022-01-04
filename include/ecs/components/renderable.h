#pragma once
#include <vector2d.h>

namespace ecs::component {

	struct Renderable {
		Renderable(int r, int g, int b) :
			red(r), green(g), blue(b) {}
		int red;
		int green;
		int blue;
	};
}