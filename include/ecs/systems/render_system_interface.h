#pragma once
#include <memory>

#include <ecs/core/system_manager.h>
#include <vector2d.h>

namespace ecs {
	namespace system {
		class RenderSystem : public ecs::core::System {
		public:
			virtual ~RenderSystem() {}
			virtual void Update(uint32_t dt) = 0;
			virtual void Render() = 0;
			virtual void Init() {}
		};

		class RenderWindow {
		public:
			virtual ~RenderWindow(){}
			virtual void Update() = 0;
			virtual void ProcessEvents() = 0;
			virtual void Draw(ecs::core::Entity entity) = 0;
		};
	}
}