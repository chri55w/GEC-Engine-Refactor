#include "StateHandler.h"
#include <iostream>

//Set up singleton instance
CStateHandler *CStateHandler::instance_ = NULL;

CStateHandler &CStateHandler::getInstance() {
	if (instance_ == NULL) {
		instance_ = new CStateHandler();
	}
	return *instance_;
}
//Clean up all states
CStateHandler::~CStateHandler() {
	for (auto state : myStates_) {
		if (state.second != nullptr) {
			state.second->onDestroy();
			delete state.second;
		}
	}
}
//initialise states on creation and run the on create function.
void CStateHandler::initState(std::string stateName, CState *newState) {
	myStates_[stateName] = newState;
	newState->onCreate();
}
//Destroy a state
void CStateHandler::destroyState(std::string stateName) {
	if (myStates_.find(stateName) != myStates_.end() && myStates_.find(stateName)->second != nullptr) {
		if (currentState == myStates_[stateName]) {
			currentState = nullptr;
		}
		myStates_[stateName]->onDestroy();
		delete myStates_[stateName];
		myStates_[stateName] = nullptr;
	} else {
		HAPI->UserMessage("ERROR: Cannot Delete Non-Initialized or Null State! '" + stateName + "'", "ERROR - State Error");
	}
}
//Change to a different state
void CStateHandler::changeState(std::string stateName) {
	if (myStates_.find(stateName) != myStates_.end() && myStates_.find(stateName)->second != nullptr) {
		if (currentState != nullptr) {
			currentState->onExit();
		}
		currentState = myStates_[stateName];
		currentState->onEnter();
	} else {
		HAPI->UserMessage("ERROR: Cannot Change to Non-Initialized or Null State! '" + stateName + "'", "ERROR - State Error");
	}
}
//update the state you are currently in
void CStateHandler::updateCurrState() {
	if (currentState != nullptr) {
		currentState->onUpdate();
	}
}
//render the state you are currently in
void CStateHandler::renderCurrState() {
	if (currentState != nullptr) {
		currentState->onRender();
	}
}