#include "inc/StateManager.hpp"

StateManager::StateManager() {
	debug("StateManager initialized.");
	warning("Primary state is Initializing.");
	_currentState = GameState::Initializing;
	info("Current state set to Initializing.");

}

StateManager::~StateManager() {

}

void StateManager::setState(const GameState newState) {
	debug("Transitioning from state %s to state %s", this->getStateName(), this->getStateName(newState));
	this->_currentState = newState;
}

GameState StateManager::getState() const {
	return _currentState;
}

const char* StateManager::getStateName(GameState gamestate) const {
	if(gamestate == GameState::None)
		gamestate = this->_currentState;

	switch (gamestate) {
	case GameState::Initializing:
		return "Initializing";
	case GameState::MainMenu:
		return "MainMenu";
	case GameState::InGame:
		return "InGame";
	case GameState::LoadingResources:
		return "LoadingResources";
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
