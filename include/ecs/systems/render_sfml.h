#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <logging/logging.h>
#include <vector2d.h>
#include <ecs/systems/render_system_interface.h>
#include <ecs/core/entity_component_system.h>

namespace ecs::system {

	class SFMLWindow : public RenderWindow {
	private:
		sf::RenderWindow window_;
		std::shared_ptr<ecs::core::EntityComponentSystem> ecs_;
	public:
		SFMLWindow(
			std::shared_ptr<ecs::core::EntityComponentSystem> ecs,
			const vector::Vector2D& size,
			const std::string& window_name);

		virtual void Update() override;
		virtual void ProcessEvents() override;
		virtual void Draw(ecs::core::Entity entity) override;
	};

	class SFMLRenderSystem : public ecs::system::RenderSystem {
	private:
		ecs::core::Entity camera_;
		std::shared_ptr<ecs::core::EntityComponentSystem> ecs_;
	public:
		SFMLRenderSystem(std::shared_ptr<ecs::core::EntityComponentSystem> ecs);

		virtual void Update(uint32_t dt) override;
		virtual void Render() override;
		virtual void Init() override;
	};

}