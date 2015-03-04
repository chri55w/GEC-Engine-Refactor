#include "Visualisation.h"
#include "Simulation.h"
//#include "World.h"
#include <HAPI_lib.h>

#pragma once
class CState
{
public:
	//Base state class

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
};