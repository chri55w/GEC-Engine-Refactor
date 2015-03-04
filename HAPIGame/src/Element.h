#include <string>
#include "Enum.h"
#include "Rectangle.h"

#pragma once
class CElement
{
	public:
		//element constructors
		CElement() : button_(false), clickable_(false), callBackID_(CEnum::buttonName::BUTTON_NONE), xPos_(0), yPos_(0), clickRect_(new CRectangle),  frameID_(0) {};
		CElement(float x_pos, float y_pos, int frameId) : button_(false), clickable_(false), callBackID_(CEnum::buttonName::BUTTON_NONE), xPos_(x_pos), yPos_(y_pos), clickRect_(new CRectangle()),  frameID_(frameId) {};
		CElement(CEnum::buttonName buttonCallback, CRectangle *clickRect, float x_pos, float y_pos, int frameId, bool clickable) : button_(true), clickable_(clickable), callBackID_(buttonCallback), xPos_(x_pos), yPos_(y_pos), clickRect_(clickRect), frameID_(frameId){};
		~CElement();

		CEnum::buttonName checkButtonPress(int click_x, int click_y);

		void updateFrame(int newFrame) { frameID_ = newFrame; }
		void setClickable(bool clickable) { clickable_ = clickable; }

		float getXPos() const { return xPos_; }
		float getYPos() const { return yPos_; }
		int getFrame() const { return frameID_; }

	private:
		bool button_;
		CEnum::buttonName callBackID_;
		bool clickable_;
		float xPos_;
		float yPos_;
		CRectangle *clickRect_ = new CRectangle();
		int frameID_ = 0;
};

