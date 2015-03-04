#include "Entity.h"
#include "Simulation.h"


CEntity::CEntity(float x_position, float y_position, CRectangle* objectSize, CRectangle *collisionRect, bool gravityEnabled, bool animationEnabled) {
	xPos_ = x_position;
	yPos_ = y_position;
	gravityEnabled_ = gravityEnabled;
	animated_ = animationEnabled;

	animationIDs_["default"] = 0;
	collisionRect_ = collisionRect;
	objectSize_ = objectSize;
}

CEntity::CEntity(float x_position, float y_position, CRectangle *collisionRect) {
	xPos_ = x_position;
	yPos_ = y_position;
	collisionRect_ = collisionRect;
	hidden_ = true;
}

CEntity::~CEntity() {
	delete collisionRect_;
	delete objectSize_;
}

void CEntity::update() {
	if (animated_) {
		SIM.updateAnimation(animationIDs_[currAnim_], currFrame_);
	}
}
int CEntity::getAnimID() {
	return animationIDs_[currAnim_];
}
void CEntity::newAnimID(std::string name, int newID) {
	animationIDs_[name] = newID;
}
void CEntity::setAnim(std::string name) {
	currAnim_ = name;
}