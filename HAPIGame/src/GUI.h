#include <HAPI_lib.h>
#include <unordered_map>
#include "Enum.h"

class CRectangle;
class CGUIContainer;
#pragma once
class CGUI
{
	public:
		CGUI();
		~CGUI();

		void renderGUI();

		void addContainer(std::string containerName, float containerXPos, float containerYPos);
		void addContainerButton(std::string containerName, std::string fileName, std::string buttonName, CRectangle spriteRect, CRectangle *buttonRect, float x_pos, float y_pos, CEnum::buttonName buttonCallBackID, bool clickable);
		void addContainerGraphic(std::string containerName, std::string fileName, std::string graphicName, CRectangle spriteRect, CRectangle frameRect, float x_pos, float y_pos);

		void updateElmentFrame(std::string containerName, std::string elementName, int newFrameID);

		CEnum::buttonName checkContainerButtons(int click_x, int click_y);
	
	private:
		std::unordered_map<std::string, CGUIContainer*> GUIContainers_;
};

