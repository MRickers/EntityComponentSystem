#pragma once
#include <ecs/utils/resource_manager.h>
#include <SFML/Graphics.hpp>
#include <logging/logging.h>

namespace ecs::util {
	class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
	public:
		TextureManager(const std::string& paths_file) : ResourceManager(paths_file) {}

		std::optional<std::shared_ptr<sf::Texture>> Load(const std::string& path) {
			auto texture = std::make_shared<sf::Texture>();
			
			return texture;
		}
	};
}