#pragma once
#include "Character.h"
#include "Input.h"
#include "Enum.h"
class CPlayer :	public CCharacter {
public:
	CPlayer(float x_pos, float y_pos, CRectangle* objectSize, CRectangle *collisionRect, int health, bool gravity, bool animation);
	~CPlayer();

	void update() override;
	void checkInput(std::vector<char> keysDown, std::vector<char> keysPressed, std::vector<CInput::mouseClick_>, std::vector<CInput::controllerButtons_> ctrlButtonsDown, std::vector<CInput::controllerButtons_> ctrlButtonsPressed, std::vector<CInput::thumbstickMove_> ctrlThumbMoves);

private:
	void movePlayer(CEnum::direction key, int dist);
	void resetJump();

	float velocity = 0;
	float maxVelocity = 10;

	bool jumping = false;
	int jumpMoves = 7;
	float jumpForce = 8;
	int jumpMovesLeft = jumpMoves;
	float upwardThrust = jumpForce;
	float forceStep = jumpForce / jumpMoves;
};

