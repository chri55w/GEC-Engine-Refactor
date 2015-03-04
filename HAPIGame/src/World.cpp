#include "World.h"
#include <iostream>
#include "SoundManager.h"
#include "Input.h"
#include "ParseData.h"
#include "Entity.h"
#include "Simulation.h"
#include "Player.h"
#include "RenderQueue.h"

CWorld *CWorld::instance_ = NULL;

CWorld & CWorld::getInstance()
{
	if (instance_ == NULL)
		instance_ = new CWorld;
	return *instance_;
}


CWorld::~CWorld() {
	for (auto entity : worldEntites_) {
		delete entity.second;
	}
}

void CWorld::createPlayer(std::string name, float x_position, float y_position, CRectangle* objsize, CRectangle* collisionRect, int health, bool gravityEnabled, bool animationEnabled) {
	CPlayer *newPlayer = new CPlayer(x_position, y_position, objsize, collisionRect, health, gravityEnabled, animationEnabled);

	worldEntites_[name] = newPlayer;
}
void CWorld::createEntity(std::string name, float x_position, float y_position, CRectangle* objsize, CRectangle* collisionRect, bool gravityEnabled, bool animationEnabled) {
	CEntity *newEntity = new CEntity(x_position, y_position, objsize, collisionRect, gravityEnabled, animationEnabled);

	worldEntites_[name] = newEntity;
}
void CWorld::createHiddenEntity(std::string name, float x_position, float y_position, CRectangle* collisionRect) {
	CEntity *newEntity = new CEntity(x_position, y_position, collisionRect);

	worldEntites_[name] = newEntity;
}



void CWorld::update() {
	AUDIO.playSound("background");
	/*
	for (background* bkgrnd : backgrounds_) {
		if (bkgrnd->scrollSpeed_ > 0.0) {
			scrollBackground(bkgrnd);
			updateBackgroundLocation(bkgrnd);
		}
	}
	*/
	checkWorldInput(INPUT.getKeysDown(), INPUT.getKeysPressed(), INPUT.getMouseClicks(), INPUT.getControllerButtonsDown(), INPUT.getControllerButtonsPressed());
	for (auto entity : worldEntites_) {
		entity.second->update();
	}
}

void CWorld::checkWorldInput(std::vector<char> keysDown, std::vector<char> keysPressed, std::vector<CInput::mouseClick_> mouseClicks, std::vector<CInput::controllerButtons_> ctrlButtonsDown, std::vector<CInput::controllerButtons_> ctrlButtonsPressed) {
	for (char key : keysPressed) {
		
	}
}

void CWorld::renderWorld() {
	/*
	for (background* bkgrnd : backgrounds_) {
		VIS.scrollRender(bkgrnd->spriteName_, (int)bkgrnd->xPos_, (int)bkgrnd->yPos_, 0, bkgrnd->blitAlpha_);
	}*/
	for (auto entity : worldEntites_) {
		//VIS.render(entity.first, entity.second->getXPos(), entity.second->getYPos(), SIM.getFrame(entity.second->getAnimID(), entity.second->getCurrFrame()), true);
		RENDERQUEUE.pushToQueue(entity.first, entity.second->getXPos(), entity.second->getYPos(), SIM.getFrame(entity.second->getAnimID(), entity.second->getCurrFrame()), entity.second->getZIndex(), true, false);
	}
}


int CWorld::getEntityXPos(std::string name) {
	return worldEntites_[name]->getXPos();
}
int CWorld::getEntityYPos(std::string name) {
	return worldEntites_[name]->getYPos();
}
CRectangle *CWorld::getEntitySize(std::string name) {
	return worldEntites_[name]->getObjSize();
}
CRectangle *CWorld::getEntityCollisionRect(std::string name) {
	return worldEntites_[name]->getCollisionRect();
}
int CWorld::getEntityAnimID(std::string name) {
	return worldEntites_[name]->getAnimID();
}
int CWorld::getEntityFrameID(std::string name) {
	return worldEntites_[name]->getCurrFrame();
}
void CWorld::addEntityAnimID(std::string name, std::string animName, int newID) {
	worldEntites_[name]->newAnimID(animName, newID);
}
void CWorld::setEntityAnim(std::string name, std::string animName) {
	worldEntites_[name]->setAnim(animName);
}


bool CWorld::checkAllEntityCollision(CEntity* entity, int distX, int distY) {
	CRectangle entityNewPos = *entity->getCollisionRect();
	entityNewPos.translate(distX +  entity->getXPos(), distY + entity->getYPos());
	for (auto e : worldEntites_) {
		if (e.second == entity) {
			continue;
		}
		CRectangle tempEntityRect = *e.second->getCollisionRect();
		tempEntityRect.translate(e.second->getXPos(), e.second->getYPos());
		if (tempEntityRect.intersects(entityNewPos)) {
			return true;
		}
	}
	return false;
}

void CWorld::moveMap(int x, int y) {
	worldPosX_ += x;
	worldPosY_ += y;
	//applyParalaxBackground(-x, -y);
}