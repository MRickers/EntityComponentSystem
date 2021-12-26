#pragma once
#include <chrono>

namespace ecs::utils {
	class Timer {
	private:
		bool started_;
		std::chrono::high_resolution_clock::time_point start_time_;
	public:
		Timer();

		void Start();
		void Stop();
		uint32_t GetTime() const;
		bool IsStarted() const;

	};
}