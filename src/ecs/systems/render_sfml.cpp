#include <ecs/systems/render_sfml.h>
#include <ecs/components/transform.h>

namespace ecs::system {
	SFMLWindow::SFMLWindow(
		std::shared_ptr<ecs::core::EntityComponentSystem> ecs,
		const vector::Vector2D& size,
		const std::string& window_name
	) :
	window_(sf::VideoMode(size.GetX(), size.GetY()), window_name),
	ecs_(ecs)
	{}

	void SFMLWindow::Update() {

	}

	void SFMLWindow::ProcessEvents() {

	}

	void SFMLWindow::Draw(ecs::core::Entity entity) {
		//const auto& transform = ecs_->GetComponent<ecs::component::Transform>(entity);
	}
}