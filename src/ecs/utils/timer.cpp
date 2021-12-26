#include <ecs/utils/timer.h>

namespace ecs::utils {
	Timer::Timer() : 
		started_(true),
		start_time_(std::chrono::high_resolution_clock::now()) {}

	void Timer::Start() {
		started_ = true;
		start_time_ = std::chrono::high_resolution_clock::now();
	}

	void Timer::Stop() {
		using namespace std::chrono_literals;

		started_ = false;
		start_time_ = std::chrono::high_resolution_clock::time_point{};
	}

	uint32_t Timer::GetTime() const {
		const auto duration = std::chrono::high_resolution_clock::now() - start_time_;
		const auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
		return duration_ms.count();
	}

	bool Timer::IsStarted() const {
		return started_;
	}
}