#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <logging/logging.h>
#include <vector2d.h>
#include <ecs/systems/render_system_interface.h>
#include <ecs/core/entity_component_system.h>

namespace ecs::system {

	class Dummy : public RenderWindow {
	private:
		sf::RenderWindow window_;
		std::shared_ptr<ecs::core::EntityComponentSystem> ecs_;
	public:
		Dummy(
			std::shared_ptr<ecs::core::EntityComponentSystem> ecs,
			const vector::Vector2D& size = vector::Vector2D{ 780,620 },
			const std::string& window_name = "Game Window");

		virtual void Update() override;
		virtual void ProcessEvents() override;
		virtual void Draw(ecs::core::Entity entity) override;
	};

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


}