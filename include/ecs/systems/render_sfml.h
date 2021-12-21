#include <string>

#include <SFML/Graphics.hpp>
#include <logging/logging.h>
#include <vector2d.h>

namespace ecs::system {
	class RenderWindow {
	private:
		sf::RenderWindow window_;
	public:
		RenderWindow(const vector::Vector2D& size = vector::Vector2D{ 780,620 }, const std::string& window_name = "Game Window") :
			window_(sf::VideoMode(size.GetX(), size.GetY()), window_name)) {}
		RenderWindow(const RenderWindow&) = delete;
		RenderWindow operator=(const RenderWindow) = delete;
	};


}