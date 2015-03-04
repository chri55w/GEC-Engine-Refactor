#pragma once
#include "State.h"
#include <functional>
#include "GUI.h"

#include "RenderQueue.h"

class CGUI;

class CGameState :	public CState
{
	public:
		CGameState();
		~CGameState();
		
		void onCreate();
		void onDestroy();
		void onEnter();
		void onExit();
		void onUpdate();
		void onRender();

		void onButton(CEnum::buttonName buttonClick);

		CGUI *stateGui = new CGUI();

		int healthpacks = 4;

		void updateHealthPackGUI();
};

