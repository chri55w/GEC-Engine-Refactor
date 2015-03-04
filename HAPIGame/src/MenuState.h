#pragma once
#include "State.h"
class CMenuState : public CState
{
public:
	CMenuState();
	~CMenuState();

	void onCreate();
	void onDestroy();
	void onEnter();
	void onExit();
	void onUpdate();
	void onRender();
};

