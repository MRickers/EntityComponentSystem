#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include <filesystem>
#include <ifstream>
#include <ecs/core/ecs_exception.h>
#include <logging/logging.h>

namespace ecs::util {
	template<typename Derived, typename T>
	class ResourceManager {
		using ResourcePtr = std::shared_ptr<T>;
		using ResourceContainer = std::unordered_map<std::string, ResourcePtr>;
		using Paths = std::unordered_map<std::string, std::string>;
		using namespace fs = std::filesystem;
	private:
		ResourceContainer resources_;
		Paths paths_;

		void loadPaths(const std::string& paths_file) {
			const auto path = fs::path(fs::current_path() / paths_file);
			if (fs::exists(path)) {
				std::ifstream paths;

				paths.open(path.string());

				if (paths.is_open()) {
					std::string line;
					while (std::getline(paths, line)) {
						std::string key;
						std::string key_path;
						std::stringstream key_stream(line);

						key_stream >> key;
						key_stream >> key_path;
						lLog(lDebug) << "Read: " << key << ":" << key_path;
						paths_.emplace(key, key_path);
					}
				}
				paths.close();

				if (ifs.fail() && !ifs.eof()) {
					const auto msg = "Logical i/o error on " + path.string();
					const int16_t syserr = errno;
					throw ecs::core::Exception{ msg, syserr };
				}

				if (ifs.bad()) {
					const auto msg = "Read or write i/o error on " + path.string();
					const int16_t syserr = errno;
					throw ecs::core::Exception{ msg, syserr };
				}

			}
		

		}
	public:
		virtual ~ResourceManager() {}
		ResourceManager(const std::string& paths_file) {
			loadPaths(paths_file);
		}

		ResourcePtr GetResource(const std::string& id) const {
			if (const auto resource = resource_.find(id); resource != resource_.end()) {
				return resource;
			}
			const auto msg = "Resource with id " + id + " not found.";
			lLog(lWarn) << msg;
			throw ecs::core::Exception{ msg, -1 };
		}

		std::string GetPath(const std::string& id) const {
			if (const auto& path = paths_.find(id); path != paths_.end()) {
				return path;
			}
			const auto msg = "Path with id " + id + " not found.";
			lLog(lWarn) << msg;
			throw ecs::core::Exception{ msg, -1 };
		}

		void RequireResource(const std::string& id) {
			if (const auto& resource = resources_.find(id); resource != resources_.end()) {
				return;
			}

			if (const auto& path = paths_.find(id); path == paths_.end()) {
				const auto msg = "Could not require " + id;
				throw ecs::core::Exception{ msg, -1 };
			}

			if (const auto resource = Load(id); resource.HasValue()) {
				resources_.emplace(id, resource);
			}
			const auto msg = "Could not load " + id;
			throw ecs::core::Exception{ msg, -2 };
		}

		std::optional<ResourcePtr> Load(const std::string& path) const {
			return static_cast<Derived*>(this)->Load(path);
		}

	};
}