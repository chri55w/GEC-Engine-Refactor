#include "Player.h"
#include "Input.h"
#include "Simulation.h"
#include "World.h"
#include <algorithm>
#include "SoundManager.h"


//construct player
CPlayer::CPlayer(float x_pos, float y_pos, CRectangle* objectSize, CRectangle *collisionRect, int health, bool gravity, bool animation) {
	xPos_ = x_pos;
	yPos_ = y_pos;
	gravityEnabled_ = gravity;
	animated_ = animation;
	health_ = health;

	animationIDs_["default"] = 0;
	collisionRect_ = collisionRect;
	objectSize_ = objectSize;
}

//destroy player
CPlayer::~CPlayer() {
	delete collisionRect_;
	delete objectSize_;
}

//Update this entity (overridden from standard entity update function)
void CPlayer::update() {
	if (animated_) {
		int animID = SIM.updateAnimation(animationIDs_[currAnim_], currFrame_);
		if (animID != animationIDs_[currAnim_]) {
			for (auto anim : animationIDs_) {
				if (anim.second == animID) {
					currAnim_ = anim.first;
					break;
				}
			}
		}
	}
	checkInput(INPUT.getKeysDown(), INPUT.getKeysPressed(), INPUT.getMouseClicks(), INPUT.getControllerButtonsDown(), INPUT.getControllerButtonsPressed(), INPUT.getThumbMoves());

	//Check for Player Jumping 
	if (jumping) {
		if (jumpMovesLeft > 0) {
			movePlayer(CEnum::direction::UP, (int)upwardThrust);
			upwardThrust -= forceStep;
			jumpMovesLeft--;
		}
		else {
			resetJump();
		}
	} else {
		velocity = SIM.getGravity(velocity, lastGravCall_);
		velocity = std::min(maxVelocity, velocity);

		movePlayer(CEnum::direction::DOWN, (int)velocity);
	}
}
//Prepares character to resume gravity and allows for another jump
void CPlayer::resetJump() {
	jumping = false;
	jumpMovesLeft = jumpMoves;
	upwardThrust = jumpForce;
	lastGravCall_ = HAPI->GetTime();
}
//Checks player related input (movement etc) (Data collected from the input singleton which updates every tick)
void CPlayer::checkInput(std::vector<char> keysDown, std::vector<char> keysPressed, std::vector<CInput::mouseClick_> mouseClicks, std::vector<CInput::controllerButtons_> ctrlButtonsDown, std::vector<CInput::controllerButtons_> ctrlButtonsPressed, std::vector<CInput::thumbstickMove_> ctrlThumbMoves) {
	for (char key : keysDown) {
		switch (key) {
		case 'W':
			break;
		case 'A':
			movePlayer(CEnum::direction::LEFT, 5);
			break;
		case 'S':
			break;
		case 'D':
			movePlayer(CEnum::direction::RIGHT, 5);
			break;
		}
	}
	for (char key : keysPressed) {
		switch (key) {
			case ' ':
				if (!jumping) {
					jumping = true;
					AUDIO.playSound("jumping");
					currAnim_ = "startJump";
				}
				break;
			case 'A':
				currAnim_ = "walkLeft";
				break;
			case 'S':
				break;
			case 'D':
				currAnim_ = "walkRight";
				break;
			default:
				break;

		}
	}
	for (CInput::thumbstickMove_ move : ctrlThumbMoves) {
		switch (move.thumbstick) {
		case CInput::thumbstickMove_::LEFT:
			if (move.x_axis > 0) {
				movePlayer(CEnum::direction::RIGHT, 5);
				currAnim_ = "walkRight";
			}
			else if (move.x_axis < 0) {
				movePlayer(CEnum::direction::LEFT, 5);
				currAnim_ = "walkLeft";
			}
			break;
		}
	}
	for (CInput::controllerButtons_ button : ctrlButtonsDown) {
		switch (button) {
		case CInput::A:
			if (!jumping) {
				jumping = true;
				AUDIO.playSound("jumping");
				currAnim_ = "startJump";
			}
			break;
		}
	}

}
//Check collision with other world entities then attempt movement using a directional enum and a distance which is modified until (if) the movement can be made.
void CPlayer::movePlayer(CEnum::direction key, int dist) {
	switch (key) {
	case CEnum::direction::UP:
		while (dist > 0) {
			if (WORLD.checkAllEntityCollision(this, 0, -dist) == false) {
				yPos_ -= dist;
			}
			dist--;
		}
		break;
	case CEnum::direction::LEFT:
		while (dist > 0) {
			if (WORLD.checkAllEntityCollision(this, -dist, 0) == false) {
				if (xPos_ > 10) {
					xPos_ -= dist;
				} else {
					WORLD.moveMap(-dist, 0);
				}
			}
			dist--;
		}
		break;
	case CEnum::direction::DOWN:
		while (dist > 0) {
			if (WORLD.checkAllEntityCollision(this, 0, dist) == false) {
				yPos_ += dist;
			}
			dist--;
		}
		break;
	case CEnum::direction::RIGHT:
		while (dist > 0) {
			if (WORLD.checkAllEntityCollision(this, dist, 0) == false) {
				if (xPos_ < 710) {
					xPos_ += dist;
				} else {
					WORLD.moveMap(dist, 0);
				}
			}
			dist--;
		}
		break;
	}
}