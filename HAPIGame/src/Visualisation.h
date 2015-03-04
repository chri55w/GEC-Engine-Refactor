#include <HAPI_lib.h>
#include <string>
#include <unordered_map>
#include "Rectangle.h"
#include "Enum.h"

class CSprite;

#pragma once
class CVisualisation {
	public:
		static CVisualisation &getInstance();
		~CVisualisation();

		bool initialize(int width, int height);
		void clearScreenGrey(int col);
		void clearScreenCol(HAPI_TColour col); 
		void clearRectGrey(HAPI_TColour col, CRectangle rectangle);
		void createSprite(const std::string &filename, const std::string &spriteName, CRectangle spriteSize, CRectangle spriteFrameSize);

		int getScreenHeight()const { return screen_rect_.height(); };
		int getScreenWidth()const { return screen_rect_.width(); };

		void setMediaLoc(std::string newLoc) { mediaLoc_ = newLoc; }

		BYTE* getScreenPtr() { return screenPtr_; }

		CRectangle getScreenRect() { return screen_rect_; }

	protected:
		CVisualisation(){};

	private:
		void render(std::string mapName, int x, int y, int frame, bool blitAlpha);
		void scrollRender(std::string mapName, int x, int y, int frame, bool blitAlpha);

		static CVisualisation *instance_;

		CRectangle screen_rect_ = CRectangle(0, 0, 0, 0);
		BYTE *screenPtr_ = nullptr;
		std::unordered_map<std::string, CSprite*> spriteMap_;

		std::string mediaLoc_ = "Media/";
};

#define VIS CVisualisation::getInstance()

