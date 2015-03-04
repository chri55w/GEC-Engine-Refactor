#include <string>
#include <unordered_map>
#include "Enum.h"

class CRectangle;
class CElement;
#pragma once
class CGUIContainer
{
public:
	CGUIContainer(float xPos, float yPos);
	~CGUIContainer();

	void createButton(std::string fileName, std::string buttonName, CRectangle spriteRect, CRectangle *buttonRect, float x_pos, float y_pos, CEnum::buttonName buttonCallBackID, bool clickable);
	void createGraphic(std::string fileName, std::string graphicName, CRectangle spriteRect, CRectangle frameRect, float x_pos, float y_pos);
	void updateElement(std::string elementName, int newFrame);
	void moveElement(float newX, float newY);
	void moveContainer(float newX, float newY);

	CEnum::buttonName checkButtons(int click_x, int click_y);

	void renderContainer();

	private:
		std::unordered_map<std::string, CElement*> ContainerElements_;
		float xPos_;
		float yPos_;
};

