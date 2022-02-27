#include <ecs/systems/render_sfml.h>
#include <ecs/components/renderable.h>
#include <ecs/components/camera.h>

namespace ecs::system {

	SFMLWindow::SFMLWindow(
		std::shared_ptr<ecs::core::EntityComponentSystem> ecs,
		const vector::Vector2D& size,
		const std::string& window_name
	) :
	window_(sf::VideoMode(size.GetX(), size.GetY()), window_name),
	ecs_(ecs),
	RenderWindow()
	{
	}

	void SFMLWindow::Update() {

	}

	void SFMLWindow::ProcessEvents() {
		if (window_.isOpen()) {
			sf::Event evnt;
			while (window_.pollEvent(evnt)) {
				if (evnt.type == sf::Event::Closed)
					window_.close();
			}
		}
		else {
			throw ecs::core::Exception{
				"Window close event",
				0,
				""
			};
		}
	}

	void SFMLWindow::Draw(ecs::core::Entity entity) {
		const auto& transform = ecs_->GetComponent<ecs::component::Transform>(entity);
		const auto& color = ecs_->GetComponent<ecs::component::Renderable>(entity);
		sf::Vector2f pos{ transform.position.GetX(), transform.position.GetY() };
		sf::RectangleShape rect{ sf::Vector2f{ 20, 20 } };
		rect.setFillColor(sf::Color{ color.red, color.green, color.blue });
		rect.setPosition(sf::Vector2f{ pos });

		window_.draw(rect);
	}

	void SFMLWindow::Clear() {
		window_.clear(sf::Color::Black);
	}

	void SFMLWindow::Display() {
		window_.display();
	}

	// SFMLRenderSystem
	SFMLRenderSystem::SFMLRenderSystem(
		std::shared_ptr<ecs::core::EntityComponentSystem> ecs,
		std::shared_ptr<RenderWindow> render_window) :
		camera_(),
		ecs_(ecs),
		RenderSystem(render_window)
	{
		
	}

	void SFMLRenderSystem::Update(uint32_t dt) {

	}

	void SFMLRenderSystem::Render() {
		render_window_->Clear();
		for (const auto& entity : entities_) {
			render_window_->Draw(entity);
		}
		render_window_->Display();
	}

	void SFMLRenderSystem::Init() {
		camera_ = ecs_->CreateEntity();
		auto camera = ecs::component::Camera{};
		camera.size = vector::Vector2D{ 400, 400 };
		camera.transform.position = Vector{ 200,200 };
		camera.transform.rotation = Vector{ 0,0 };
		camera.transform.scale = Vector{ 0,0 };
		ecs_->AddComponent<ecs::component::Camera>(camera_, camera);
	}
}