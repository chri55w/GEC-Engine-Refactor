#include <iostream>
#include <vector>
#include <HAPI_lib.h>


#include "Rectangle.h"


class CAnimation;

#pragma once
class CSimulation {
	public:
		static CSimulation &getInstance();
		~CSimulation();
		int newAnimation(std::vector<int> spriteSequence);
		int newAnimation(std::vector<int> spriteSequence, int nextID);

		int updateAnimation(int id, int &currFrame);

		int getFrame(int id, int currFrame);

		float getGravity(float velocity, DWORD &lastCall);
		void setFrameRate(int newFPS);

		void updateBackgrounds();
		

	protected:
		CSimulation();
	private:
		static CSimulation *instance_;
		CAnimation* anim_ = nullptr;
};

#define SIM CSimulation::getInstance()