#pragma once
#include <vector>
#include <memory>
#include <pair>
#include <ecs/state/state_base.h>

namespace ecs::state {
	using State = ecs::state::StateBase;
	using StatePtr = std::shared_ptr<State>;
	// no map, we want a stack like order of states
	using StateContainer = std::vector < std::pair<ecs::state::StateType, StatePtr>;
	using TypeContainer = std::vector<ecs::state::StateType>;

	class StateManager {
	private:
		StateContainer states_;
		TypeContainer state_types_;
	public:
		StateManager();

		void Update(uint32_t dt);
		void Render();
		void ProcessRequests();
		bool HasState(ecs::state::StateType state) const;
		void SwitchTo(ecs::state::StateType state);
		void Remove(ecs::state::StateType state);

		void AddState(ecs::state::StateType state_type, const StatePtr state);

	};
}