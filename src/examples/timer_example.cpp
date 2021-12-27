#include <ecs/utils/timer.h>
#include <logging/logging.h>
#include <thread>

int main() {
	using namespace std::chrono_literals;

	lLog(lWarn) << "Timer example";
	ecs::utils::Timer timer;
	std::this_thread::sleep_for(1000ms);
	lLog(lInfo) << "Sleept for " << timer.GetTime() << "ms";

	float fps = 0;
	int count = 0;
	timer.Start();
	while (true) {
		if (const auto dt = timer.GetTime(); dt >= 16) {
			timer.Start();
			fps += dt;
			count++;
			if (fps >= 1000) {
				fps /= count*1000;
				lLog(lDebug) << "FPS: " << 1/fps;
				count = 0;
			}
		}
	}
	return 0;
}