#pragma once

namespace ecs::state {
	class StateBase {
	protected:
		// dont render state, but update
		bool transparent_;
		// render state in order on stack
		bool transcended_;
	public:
		virtual ~StateBase() {}

		virtual void Init() = 0;
		virtual void ReInit() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void CleanUp() = 0;
		virtual void ProcessEvents() = 0;
		virtual void Update(uint32_t dt) = 0;
		virtual void Render() = 0;

		void SetTransparent(bool transparent) { transparent_ = transparent; }
		void SetTranscended(bool transcended) { transcended_ = transcended; }
		bool IsTransparent() const { return transparent_; }
		bool IsTranscended() const { return transcended_; }
	};

	enum class StateType : int32_t {
		Intro,
		MainMenu,
		Game,
		Paused,
		GameOver,
		Credits
	};
}