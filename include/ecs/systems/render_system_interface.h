#pragma once
#include <memory>

#include <ecs/core/system_manager.h>
#include <vector2d.h>

namespace ecs::system {

	class RenderWindow {
	public:
		virtual ~RenderWindow(){}
		virtual void Update() = 0;
		virtual void ProcessEvents() = 0;
		virtual void Draw(ecs::core::Entity entity) = 0;
		virtual void Clear() = 0;
		virtual void Display() = 0;
	};

	class RenderSystem : public ecs::core::System {
	protected:
		std::shared_ptr<RenderWindow> render_window_;
	public:
		RenderSystem(std::shared_ptr<RenderWindow> render_window): render_window_(render_window) {}
		virtual ~RenderSystem() {}
		virtual void Update(uint32_t dt) = 0;
		virtual void Render() = 0;
		virtual void Init() = 0;
	};
}