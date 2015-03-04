#include <HAPI_lib.h>
#include <time.h>
#include <map>

//Include Singleton Classes
#include "visualisation.h"
#include "Simulation.h"
#include "StateHandler.h"
#include "World.h"
#include "Input.h"
#include "Config.h"
#include "SoundManager.h"

//Include States
#include "GameState.h"
#include "MenuState.h"


void HAPI_Main() {
	if (!VIS.initialize(768, 448)) {
		return;
	}
	//Set HAPI font and Tell HAPI to show the FPS Counter
	HAPI->ChangeFont("Arial", 14, 1000);
	HAPI->SetShowFPS(true, 0, 0);

	//Initialise States 
	STATEHANDLER.initState("gameState", new CGameState);
   	STATEHANDLER.initState("menuState", new CMenuState);

	//Set Starting State
	STATEHANDLER.changeState("gameState");

	INPUT.setInputKeys(std::vector <char> {'W', 'A', 'S', 'D', ' '});

	unsigned int updateTick = 30; // How many times to update per second ( EG: 50 = update once every 50th of a second)
	DWORD lastUpdate = HAPI->GetTime();

	while (HAPI->Update() ) {
		//Call Render and Update funtions for the current state
		if (HAPI->GetTime() - lastUpdate > (1000 / updateTick)) {
			INPUT.readInput();
			STATEHANDLER.updateCurrState();

			lastUpdate = HAPI->GetTime();
		}
		STATEHANDLER.renderCurrState();

	}
	//Clean Up!
	delete &VIS;
	delete &SIM;
	delete &WORLD;
	delete &STATEHANDLER;
	delete &INPUT;
	delete &CONFIG;
	delete &AUDIO;
}