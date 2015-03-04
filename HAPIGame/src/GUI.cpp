#include "GUI.h"
#include "Rectangle.h"
#include "Element.h"
#include "Visualisation.h"
#include "GUIContainer.h"


CGUI::CGUI() {

}

CGUI::~CGUI() {
	for (auto c : GUIContainers_) {
		delete c.second;
	}
}

//Create containers for graphics/buttons ets
void CGUI::addContainer(std::string containerName, float containerXPos, float containerYPos) {
	CGUIContainer *newContainer = new CGUIContainer(containerXPos, containerYPos);

	GUIContainers_[containerName] = newContainer;
}
//Create a new container button
void CGUI::addContainerButton(std::string containerName, std::string fileName, std::string buttonName, CRectangle spriteRect, CRectangle *buttonRect, float x_pos, float y_pos, CEnum::buttonName buttonCallBackID, bool clickable) {
	if (GUIContainers_.find(containerName) != GUIContainers_.end()) {
		GUIContainers_[containerName]->createButton(fileName, buttonName, spriteRect, buttonRect, x_pos, y_pos, buttonCallBackID, clickable);
	}
}
//Create a new container graphic
void CGUI::addContainerGraphic(std::string containerName, std::string fileName, std::string graphicName, CRectangle spriteRect, CRectangle frameRect, float x_pos, float y_pos) {
	if (GUIContainers_.find(containerName) != GUIContainers_.end()) {
		GUIContainers_[containerName]->createGraphic(fileName, graphicName, spriteRect, frameRect, x_pos, y_pos);
	}
}
//Render all GUI graphics
void CGUI::renderGUI() {
	for (auto element : GUIContainers_) {
		element.second->renderContainer();
	}
}
//Check all buttons for clicks and return any button types of clicked buttons
CEnum::buttonName CGUI::checkContainerButtons(int click_x, int click_y) {
	for (auto button : GUIContainers_) {
		CEnum::buttonName buttonVal = button.second->checkButtons(click_x, click_y);
		if (buttonVal != CEnum::buttonName::BUTTON_NONE) {
			return buttonVal;
		}
	}
	return CEnum::buttonName::BUTTON_NONE;
}

//update an element frame to represent state etc.
void CGUI::updateElmentFrame(std::string containerName, std::string elementName, int newFrameID) {
	if (GUIContainers_.find(containerName) != GUIContainers_.end()) {
		GUIContainers_[containerName]->updateElement(elementName, newFrameID);
	}
}