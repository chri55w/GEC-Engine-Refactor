#include "GUIContainer.h"
#include "Element.h"
#include "RenderQueue.h"

//Container constructor
CGUIContainer::CGUIContainer(float xPos, float yPos) {
	yPos_ = yPos;
	xPos_ = xPos;
}
//Container cleanup
CGUIContainer::~CGUIContainer() {
	for (auto e : ContainerElements_) {
		delete e.second;
	}
}
//Create a new button within this container
void CGUIContainer::createButton(std::string fileName, std::string buttonName, CRectangle spriteRect, CRectangle *buttonRect, float x_pos, float y_pos, CEnum::buttonName buttonCallBackID, bool clickable) {

	VIS.createSprite(fileName, buttonName, spriteRect, *buttonRect);
	CElement *newElement = new CElement(buttonCallBackID, buttonRect, x_pos, y_pos, 0, clickable);

	ContainerElements_[buttonName] = newElement;
}
//Create a new graphic within this container
void CGUIContainer::createGraphic(std::string fileName, std::string graphicName, CRectangle spriteRect, CRectangle frameRect, float x_pos, float y_pos) {

	VIS.createSprite(fileName, graphicName, spriteRect, frameRect);
	CElement *newElement = new CElement(x_pos, y_pos, 0);

	ContainerElements_[graphicName] = newElement;
}
//Update element frame to correspond to passed in data etc
void CGUIContainer::updateElement(std::string elementName, int newFrame) {
	if (ContainerElements_.find(elementName) != ContainerElements_.end()) {
		ContainerElements_[elementName]->updateFrame(newFrame);
	}
}
//check all buttons within this container for clicks and return button types for any clicked buttons
CEnum::buttonName CGUIContainer::checkButtons(int click_x, int click_y) {
	for (auto button : ContainerElements_) {
		CEnum::buttonName buttonVal = button.second->checkButtonPress((int)(click_x-xPos_), (int)(click_y-yPos_));
		if (buttonVal != CEnum::buttonName::BUTTON_NONE) {
			return buttonVal;
		}
	}
	return CEnum::buttonName::BUTTON_NONE;
}
//render this containers GUI buttons
void CGUIContainer::renderContainer() {
	for (auto element : ContainerElements_) {
		VIS.render(element.first, (int)(element.second->getXPos() + xPos_), (int)(element.second->getYPos() + yPos_), element.second->getFrame(), true);
	}
}
//move this container and all objects within it
void CGUIContainer::moveContainer(float newX, float newY) {
	xPos_ = newX;
	yPos_ = newY;
}