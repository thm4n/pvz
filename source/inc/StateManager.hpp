#pragma once

#include "Logger.hpp"

enum class GameState {
	None = -1,
	Exit = 0,
	Initializing = 1,
	LoadingResources,
	MainMenu,
	InGame,
	GameOver,
	Paused,
	Settings,
};

class StateManager {
public:
	StateManager();
	~StateManager();

	void setState(const GameState newState);
	GameState getState() const;
	const char* getStateName(GameState gamestate = GameState::None) const;

private:
	GameState _currentState;
};
