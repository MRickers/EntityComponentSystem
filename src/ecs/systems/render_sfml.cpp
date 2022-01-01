#include <ecs/systems/render_sfml.h>
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

	}

	void SFMLWindow::Draw(ecs::core::Entity entity) {
		//const auto& transform = ecs_->GetComponent<ecs::component::Transform>(entity);
	}

	// SFMLRenderSystem
	SFMLRenderSystem::SFMLRenderSystem(std::shared_ptr<ecs::core::EntityComponentSystem> ecs) :
		camera_(),
		ecs_(ecs) {
		
	}

	void SFMLRenderSystem::Update(uint32_t dt) {

	}

	void SFMLRenderSystem::Render() {

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