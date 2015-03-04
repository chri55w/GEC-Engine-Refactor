#include "Input.h"
#include <iostream>
#include <HAPI_lib.h>

CInput * CInput::instance_ = NULL;

CInput &CInput::getInstance() {
	if (instance_ == NULL) {
		instance_ = new CInput();
	}
	return *instance_;
}
//read input for this tick
void CInput::readInput() {
	keysPressed_.clear();
	controlButtonsPressed_.clear();
	mouseClicks_.clear();			//controls maximum keyboard checks per second
	HAPI->GetKeyboardData(&keyboard_);
	HAPI->GetMouseData(&mouse_);
	if (HAPI->GetControllerData(0, &controller_)) {
		checkControllerInput();
	}
	checkKeyboardInput();
	checkMouseInput();
}
//check for keyboard buttons down (only check defined key checks to maintain high FPS), also check for button pressed (buttons down that werent down last check)
void CInput::checkKeyboardInput() {
	for (char key : inputKeys_) {
		bool press = true;
		for (char keyDown : keysDown_) {
			if (keyDown == key) {
				press = false;
				break;
			}
		}
		if (keyboard_.scanCode[key] == true && press) {
			keysPressed_.push_back(key);
		}
	} 
	keysDown_.clear();
	for (char key : inputKeys_) {
		if (keyboard_.scanCode[key] == true) {
			keysDown_.push_back(key);
		}
	}
}
//check for mouse clicks, this will not allow the mouse to be held down it will process the data only if the mouse button was not clicked on the last check
void CInput::checkMouseInput() {
	bool clickLeft = true;
	bool clickRight = true;
	bool clickMiddle = true;
	for (mouseClick_ click : mouseDowns_) {
		if (click.clickType == mouseClick_::LEFT) {
			clickLeft = false;
		} else if (click.clickType == mouseClick_::RIGHT) {
			clickRight = false;
		} else if (click.clickType == mouseClick_::MIDDLE) {
			clickMiddle = false;
		}
	}
	mouseDowns_.clear();
	if (mouse_.leftButtonDown == true) {
		mouseClick_ newMouseClick;
		newMouseClick.clickType = mouseClick_::LEFT;
		newMouseClick.x_pos = mouse_.x;
		newMouseClick.y_pos = mouse_.y;
		mouseDowns_.push_back(newMouseClick);
		if (clickLeft)  {
			mouseClicks_.push_back(newMouseClick);
		}
	}
	if (mouse_.middleButtonDown == true) {
		mouseClick_ newMouseClick;
		newMouseClick.clickType = mouseClick_::MIDDLE;
		newMouseClick.x_pos = mouse_.x;
		newMouseClick.y_pos = mouse_.y;
		mouseDowns_.push_back(newMouseClick);
		if (clickMiddle) {
			mouseClicks_.push_back(newMouseClick);
		}
	}
	if (mouse_.rightButtonDown == true) {
		mouseClick_ newMouseClick;
		newMouseClick.clickType = mouseClick_::RIGHT;
		newMouseClick.x_pos = mouse_.x;
		newMouseClick.y_pos = mouse_.y;
		mouseClicks_.push_back(newMouseClick);
		if (clickRight) {
			mouseClicks_.push_back(newMouseClick);
		}
	}
}
//Check all controller input, from triggers to thumbsticks and buttons (down or pressed - as described for the keyboard input)
void CInput::checkControllerInput() {
	thumbMoves_.clear();
	int LX_axis = controller_.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LY_axis = controller_.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int RX_axis = controller_.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X];
	int RY_axis = controller_.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y];
	int LThumb_deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	int RThumb_deadzone = HK_GAMEPAD_RIGHT_THUMB_DEADZONE;
	if (LX_axis > LThumb_deadzone || LX_axis < -LThumb_deadzone || LY_axis > LThumb_deadzone || LY_axis < -LThumb_deadzone) {
		thumbstickMove_ newThumbMove;
		newThumbMove.thumbstick = thumbstickMove_::LEFT;
		newThumbMove.x_axis = LX_axis;
		newThumbMove.y_axis = LY_axis;
		thumbMoves_.push_back(newThumbMove);
	}
	if (RX_axis > RThumb_deadzone || RX_axis < -RThumb_deadzone || RY_axis > RThumb_deadzone || RY_axis < -RThumb_deadzone) {
		thumbstickMove_ newThumbMove;
		newThumbMove.thumbstick = thumbstickMove_::RIGHT;
		newThumbMove.x_axis = LX_axis;
		newThumbMove.y_axis = LY_axis;
		thumbMoves_.push_back(newThumbMove);
	}
	if (controller_.analogueButtons[HK_ANALOGUE_LEFT_TRIGGER] > 0) {
		triggerMove_ newTrigger;
		newTrigger.trigger = triggerMove_::LEFT;
		newTrigger.value = controller_.digitalButtons[HK_ANALOGUE_LEFT_TRIGGER];
	}
	if (controller_.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] > HK_GAMEPAD_TRIGGER_THRESHOLD) {
		triggerMove_ newTrigger;
		newTrigger.trigger = triggerMove_::RIGHT;
		newTrigger.value = controller_.digitalButtons[HK_ANALOGUE_RIGHT_TRIGGER];
	}

	for (int buttonIdx = 0; buttonIdx < 15; buttonIdx++) {
		bool press = true;
		for (int button : controlButtonsDown_) {
			if (buttonIdx == button) {
				press = false;
				break;
			}
		}
		if (controller_.digitalButtons[buttonIdx] && press) {
			controlButtonsPressed_.push_back(controllerButtons_(buttonIdx));
		}
	}
	controlButtonsDown_.clear();
	for (int buttonIdx = 0; buttonIdx < 15; buttonIdx++) {
		if (controller_.digitalButtons[buttonIdx]) {
			controlButtonsDown_.push_back(controllerButtons_(buttonIdx));
		}
	}
}