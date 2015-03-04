#include <HAPI_lib.h>
#include <vector>
#include "Enum.h"
#include "Input.h"
#include "Level.h"
#include <unordered_map>

class CEntity;
class CRectangle;
#pragma once
class CWorld {
	public:
		static CWorld &getInstance();
		~CWorld();
		
		void createPlayer(std::string name, float x_position, float y_position, CRectangle* objsize, CRectangle* collisionRect, int health, bool gravityEnabled, bool animationEnabled);
		void createNPC(std::string name, float x_position, float y_position, CRectangle* objsize, CRectangle* collisionRect, int health, bool gravityEnabled, bool animationEnabled);
		void createEntity(std::string name, float x_position, float y_position, CRectangle* objsize, CRectangle* collisionRect, bool gravityEnabled, bool animationEnabled);
		void createHiddenEntity(std::string name, float x_position, float y_position, CRectangle* collisionRect);

		void update();

		void renderWorld();

		int getEntityXPos(std::string name);
		int getEntityYPos(std::string name);
		CRectangle *getEntitySize(std::string name);
		CRectangle *getEntityCollisionRect(std::string name);

		int getEntityAnimID(std::string name);
		int getEntityFrameID(std::string name);
		void addEntityAnimID(std::string name, std::string animName, int newID);
		void setEntityAnim(std::string name, std::string animName);
		void setEntityAnim(CEntity* entity, std::string animName);

		int getMapXPos() const { return worldPosX_; }
		int getMapYPos() const { return worldPosY_; }

		void moveMap(int x, int y);

		bool checkAllEntityCollision(CEntity* entity, int distX, int distY);

	protected:
		CWorld() {};

	private:
		static CWorld *instance_;

		std::unordered_map<std::string, CEntity*> worldEntites_;
		void checkWorldInput(std::vector<char> keysDown, std::vector<char> keysPressed, std::vector<CInput::mouseClick_> mouseClicks, std::vector<CInput::controllerButtons_> ctrlButtonsDown, std::vector<CInput::controllerButtons_> ctrlButtonsPressed);

		int worldPosX_ = 300;
		int worldPosY_ = 300;
};

#define WORLD CWorld::getInstance()


