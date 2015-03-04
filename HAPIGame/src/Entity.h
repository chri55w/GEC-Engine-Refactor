#include "Rectangle.h"
#include <unordered_map>
#include <HAPI_lib.h>

#pragma once
class CEntity {
public:
		CEntity() {};
		CEntity(float x_position, float y_position, CRectangle *collisionRect);
		CEntity(float x_position, float y_position, CRectangle* objectSize, CRectangle *collisionRect, bool gravityEnabled, bool animationEnabled);
		~CEntity();

		int getXPos() const { return (int)xPos_; }
		int getYPos() const { return (int)yPos_; }
		CRectangle *getObjSize() const { return objectSize_; }
		CRectangle *getCollisionRect() const { return collisionRect_; }
		int getZIndex() const { return zIndex_; }

		int getAnimID();
		int getCurrFrame() const { return currFrame_; }
		void newAnimID(std::string name, int newID);
		void setAnim(std::string name);

		virtual void update();

	protected:
		int zIndex_ = 0;
		bool hidden_ = false;
		float xPos_;
		float yPos_;
		CRectangle *objectSize_ =  nullptr;
		CRectangle *collisionRect_ = nullptr;

		bool onGround_ = true;
		bool gravityEnabled_ = false;
		float fallSpeed_;
		DWORD lastGravCall_ = HAPI->GetTime();

		bool animated_ = false;
		std::unordered_map<std::string, int> animationIDs_;
		std::string currAnim_ = "default";
		int currFrame_;
};

