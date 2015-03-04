#include <unordered_map>
#include "state.h"

#pragma once
class CStateHandler
{
	public:
		static CStateHandler &getInstance();
		~CStateHandler();

		void initState(std::string stateName, CState *newState);
		void destroyState(std::string stateName);
		void renderCurrState();
		void updateCurrState();
		void changeState(std::string stateName);

	protected:
		CStateHandler() {};
	private:
		static CStateHandler *instance_;
		std::unordered_map < std::string, CState*> myStates_;
		CState *currentState;
};

#define STATEHANDLER CStateHandler::getInstance()
