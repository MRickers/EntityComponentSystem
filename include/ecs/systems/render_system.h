#pragma once
#include <memory>

#include "ecs/core/system_manager.h"

namespace ecs {
	namespace system {
		class RenderSystem : public ecs::core::System {
		private:

		public:
			virtual ~RenderSystem() {}
			virtual void Update(uint32_t dt) = 0;
			virtual void Render() = 0;
			virtual void Init() {}
		};

		enum class Renderlib : int {
			Sdl2,
			SFML,
		};

		class RenderSystemFactory {
		public:
			std::unique_ptr<RenderSystem> MakeSystem(const Renderlib renderlib)  const;
		};
	}
}