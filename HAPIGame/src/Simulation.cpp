#include "Simulation.h"
#include "Animation.h"

//Singleton instance setup
CSimulation *CSimulation::instance_ = NULL;

CSimulation &CSimulation::getInstance() {
	if (instance_ == NULL) {
		instance_ = new CSimulation();
	}
	return *instance_;
}
//Create simulation handler, creating any handler data required
CSimulation::CSimulation() {
	anim_ = new CAnimation();
}
//Clean up any dynamic data
CSimulation::~CSimulation() {
	delete anim_;
}
//Create a new animation in the animation handler
int CSimulation::newAnimation(std::vector<int> spriteSequence) {
	return anim_->newAnimation(spriteSequence);
}
//Create a new animation in the animation handler with a next animation id to pass on to
int CSimulation::newAnimation(std::vector<int> spriteSequence, int nextID) {
	return anim_->newAnimation(spriteSequence, nextID);
}
//Update the current animation frame
int CSimulation::updateAnimation(int id, int &currFrame) {
	id = anim_->updateFrame(id, currFrame);

	return id;
}
//get the current frame local to the spritesheet based on the current animation and the frame id within that animation.
int CSimulation::getFrame(int id, int currFrame) { 
	return anim_->getFrame(id, currFrame); 
}
//Calcluate gravity fall values to implement acceleration etc and simular freefall
float CSimulation::getGravity(float velocity, DWORD &lastCall) {
	//Get the Current Time
	DWORD currTime = HAPI->GetTime();

	//Calculate the time since the last application of gravity
	int timeSince = currTime - lastCall;
	float timeSinceLast = timeSince / 1000.0f;

	//Using real world rate of acceleration in freefall multiply by the number of pixels in a virtual metre
	float freeFallVal = 9.81f * 32;

	//Modulate the freefall value to 'fudge' the illusion of air resistance etc
	float fallValue = freeFallVal * 0.4f;

	//Using the time since the last application modify the acceleration by to consider per second calculation
	float acceleration = timeSinceLast * fallValue;

	//Add acceleration to the current velocity 
	velocity += acceleration;

	//Update the last gravity call to this one
	lastCall = HAPI->GetTime();

	return velocity;
}
//set the current frame rate
void CSimulation::setFrameRate(int newFPS) {
	anim_->setFrameRate(newFPS);
}