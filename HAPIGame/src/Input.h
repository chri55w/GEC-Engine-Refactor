#include <vector>
#include <HAPI_lib.h>

#pragma once
class CInput
{
	public:
		struct mouseClick_ {
			enum EClickType { LEFT, MIDDLE, RIGHT };
			EClickType clickType;
			int x_pos;
			int y_pos;
		};
		struct thumbstickMove_ {
			enum EThumbstick { LEFT, RIGHT };
			EThumbstick thumbstick;
			int x_axis;
			int y_axis;
		};
		struct triggerMove_ {
			enum ETrigger { LEFT, RIGHT };
			ETrigger trigger;
			int value;
		};
		enum controllerButtons_{ DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT, START, BACK, LEFT_THUMB, RIGHT_THUMB, LEFT_SHOULDER, RIGHT_SHOULDER, A, B, X, Y, VOL_UP, VOL_DOWN};

		static CInput &getInstance();
		void readInput();
		std::vector<char> getKeysDown() const { return keysDown_; }
		std::vector<char> getKeysPressed() const { return keysPressed_; }
		std::vector<mouseClick_> getMouseClicks() const { return mouseClicks_; }
		std::vector<thumbstickMove_> getThumbMoves() const { return thumbMoves_; }
		std::vector<controllerButtons_> getControllerButtonsDown() const { return controlButtonsDown_; }
		std::vector<controllerButtons_> getControllerButtonsPressed() const { return controlButtonsPressed_; }

		void setInputKeys(std::vector<char> keysToRead) { inputKeys_ = keysToRead; }
		
		~CInput() {};

	protected:
		CInput() {};

	private:
		static CInput *instance_;
		std::vector<char> keysDown_;
		std::vector<char> keysPressed_;
		std::vector<mouseClick_> mouseClicks_;
		std::vector<mouseClick_> mouseDowns_;
		std::vector<thumbstickMove_> thumbMoves_;
		std::vector<controllerButtons_> controlButtonsDown_;
		std::vector<controllerButtons_> controlButtonsPressed_;
		HAPI_TKeyboardData keyboard_;
		HAPI_TMouseData mouse_;
		HAPI_TControllerData controller_;

		std::vector<char> inputKeys_;

		void checkKeyboardInput();
		void checkMouseInput();
		void checkControllerInput();
};

#define INPUT CInput::getInstance()