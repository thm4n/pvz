#pragma once

#include <iostream>

#include "Logger.hpp"

class StateManager {
public:
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

	StateManager() {
		debug("StateManager initialized.");
		warning("Primary state is Initializing.");
		_currentState = GameState::Initializing;
		info("Current state set to Initializing.");

	}

	~StateManager() {

	}

	void setState(const GameState newState) {
		debug("Transitioning from state %s to state %s", this->getStateName(), this->getStateName(newState));
		this->_currentState = newState;
	}

	GameState getState() const {
		return _currentState;
	}

	const char* getStateName(GameState gamestate = GameState::None) const {
		if(gamestate == GameState::None)
			gamestate = this->_currentState;

		switch (gamestate) {
		case GameState::Initializing:
			return "Initializing";
		case GameState::MainMenu:
			return "MainMenu";
		case GameState::InGame:
			return "InGame";
		case GameState::GameOver:
			return "GameOver";
		case GameState::Paused:
			return "Paused";
		case GameState::Settings:
			return "Settings";
		case GameState::Exit:
			return "Exit";
		}
		return "Undefined State";
	}

private:
	GameState _currentState;
};
