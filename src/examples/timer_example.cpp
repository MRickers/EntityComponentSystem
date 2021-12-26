#include <ecs/utils/timer.h>
#include <logging/logging.h>
#include <thread>

int main() {
	using namespace std::chrono_literals;

	lLog(lWarn) << "Timer example";
	ecs::utils::Timer timer;
	std::this_thread::sleep_for(1000ms);
	lLog(lInfo) << "Sleept for " << timer.GetTime() << "ms";
	return 0;
}