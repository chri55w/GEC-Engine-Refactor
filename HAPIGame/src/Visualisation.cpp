#include "visualisation.h"
#include "sprite.h"
#include "Rectangle.h"
#include <ctgmath>

//Singleton Instance setup
CVisualisation *CVisualisation::instance_ = NULL;

CVisualisation & CVisualisation::getInstance()
{
	if (instance_ == NULL)
		instance_ = new CVisualisation;
	return *instance_;
}
//Clean up sprites
CVisualisation::~CVisualisation() {
	for (auto p : spriteMap_) {
		delete p.second;
	}
}
//initialise HAPI
bool CVisualisation::initialize(int w, int h) {
	int height = h;
	int width = w;
	if (!HAPI->Initialise(&width, &height)) {
		return false;
	}
	screen_rect_ = CRectangle(0, width, 0, height);
	screenPtr_ = HAPI->GetScreenPointer();
	return true; 
}
//Clear a rectangle to a colour - for debugging rectangles
void CVisualisation::clearRectGrey(HAPI_TColour col, CRectangle rectangle) {
	int height = rectangle.height();
	int width = rectangle.width();
	int x_pos = rectangle.getLeft();
	int y_pos = rectangle.getTop();
	int offset = x_pos + (screen_rect_.width() * y_pos);
	int lineOffset = screen_rect_.width() - width;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			BYTE* p_pixel = screenPtr_ + (offset * 4);
			memcpy(p_pixel, &col, 4);
			offset++;
		}
		offset += lineOffset ;
	}
}
//clear entire screen to a greyscale colour
void CVisualisation::clearScreenGrey(int col) {
	memset(screenPtr_, col, screen_rect_.width() * screen_rect_.height() * 4);
}
// clear screen to a hapit_colour
void CVisualisation::clearScreenCol(HAPI_TColour col) {
	int offset = 0;
	for (int i = 0; i < (screen_rect_.height() * screen_rect_.width()); i++) {
		BYTE *p_pixel = screenPtr_ + offset;
		memcpy(p_pixel, &col, 4);
		offset += 4;
	}
}
//create a new sprite
void CVisualisation::createSprite(const std::string &filename, const std::string &spriteName, CRectangle spriteSize, CRectangle spriteFrameSize) {
	CSprite *newSprite = new CSprite(spriteSize, spriteFrameSize);
	if (!newSprite->loadSprite(mediaLoc_ + filename)) {
		HAPI->UserMessage("Error loading texture. \nProgram will exit.", "Error");
		return;
	}
	spriteMap_[spriteName] = newSprite;
}
//render a single sprite
void CVisualisation::render(std::string mapName, int x, int y, int frame, bool blitAlpha) {
	if (spriteMap_.find(mapName) != spriteMap_.end()) {
		spriteMap_[mapName]->renderSprite(screenPtr_, screen_rect_, x, y, frame, blitAlpha);
	}
}
//render any size sprite to cover the entire screen
void CVisualisation::scrollRender(std::string mapName, int x, int y, int frame, bool blitAlpha) {
	if (spriteMap_.find(mapName) != spriteMap_.end()) {
		int sprite_width = spriteMap_[mapName]->getSpriteFrameWidth();
		int sprite_height = spriteMap_[mapName]->getSpriteFrameHeight();

		int startX = x - (int)(sprite_width * ceil(x / (sprite_width * 1.0f)));
		int startY = y - (int)(sprite_height * ceil(y / (sprite_height * 1.0f)));

		int currentX = startX;
		int currentY = startY;

		while (currentX < screen_rect_.width()) {
			while (currentY < screen_rect_.height()) {
				spriteMap_[mapName]->renderSprite(screenPtr_, screen_rect_, currentX, currentY, frame, blitAlpha);
				currentY += sprite_height;
			}
			currentX += sprite_width;
			currentY = startY;
		}
	}
}