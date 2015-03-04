#include "Element.h"


CElement::~CElement() {
	delete clickRect_;
}
//Check for clicked in the button rectangle using mouse click coordinates, if button clicked return the button type
CEnum::buttonName CElement::checkButtonPress(int click_x, int click_y) {
	CRectangle mouseRect = CRectangle(click_x, click_x + 1, click_y, click_y + 1);
	clickRect_->translate((int)xPos_, (int)yPos_);
	CEnum::buttonName returnVal = CEnum::buttonName::BUTTON_NONE;

	if (clickable_) {
		if (mouseRect.completelyInside(*clickRect_)) {
			returnVal = callBackID_;
		}
	}
	clickRect_->translate((int)-xPos_, (int)-yPos_);
	return returnVal;
}