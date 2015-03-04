#include "Background.h"


CBackground::CBackground() {

}


CBackground::~CBackground() {
	for (background* bkgrnd : backgrounds_) {
		delete bkgrnd;
	}
}

void CBackground::createBackground(std::string spriteName, float x_pos, float y_pos, int width, int height, bool blitAlpha, CEnum::direction direction_to_scroll, float scrolling_speed) {
	background* newBkgrnd = new background();
	newBkgrnd->spriteName_ = spriteName;
	newBkgrnd->xPos_ = x_pos;
	newBkgrnd->yPos_ = y_pos;
	newBkgrnd->width_ = width;
	newBkgrnd->height_ = height;
	newBkgrnd->blitAlpha_ = blitAlpha;
	newBkgrnd->scrollSpeed_ = scrolling_speed;
	newBkgrnd->moveDir_ = direction_to_scroll;

	backgrounds_.push_back(newBkgrnd);
}

void CBackground::createBackground(std::string spriteName, float x_pos, float y_pos, int width, int height, bool blitAlpha, float paralax_modifier) {
	background* newBkgrnd = new background();
	newBkgrnd->spriteName_ = spriteName;
	newBkgrnd->xPos_ = x_pos;
	newBkgrnd->yPos_ = y_pos;
	newBkgrnd->width_ = width;
	newBkgrnd->height_ = height;
	newBkgrnd->blitAlpha_ = blitAlpha;
	newBkgrnd->paralaxModifier_ = paralax_modifier;

	backgrounds_.push_back(newBkgrnd);
}

void CBackground::scrollBackground(background* bkgrnd) {
	switch (bkgrnd->moveDir_) {
	case CEnum::direction::UP:
		bkgrnd->yPos_ -= bkgrnd->scrollSpeed_;
		break;
	case CEnum::direction::DOWN:
		bkgrnd->yPos_ += bkgrnd->scrollSpeed_;
		break;
	case CEnum::direction::LEFT:
		bkgrnd->xPos_ -= bkgrnd->scrollSpeed_;
		break;
	case CEnum::direction::RIGHT:
		bkgrnd->xPos_ += bkgrnd->scrollSpeed_;
		break;
	case CEnum::direction::DIRECTION_NONE:
		break;
	}
}

void CBackground::updateBackgroundLocation(background* bkgrnd, int worldX, int worldY, int screenWidth, int screenHeight) {
	if (bkgrnd->xPos_ + worldX + bkgrnd->width_ < 0 + screenWidth) {
		bkgrnd->xPos_ += bkgrnd->width_;
	}
	if (bkgrnd->xPos_ + worldX > bkgrnd->width_) {
		bkgrnd->xPos_ -= bkgrnd->width_;
	}
	if (bkgrnd->yPos_ + worldY + bkgrnd->height_ < 0 + screenHeight) {
		bkgrnd->yPos_ += bkgrnd->height_;
	}
	if (bkgrnd->yPos_ + worldY > bkgrnd->height_) {
		bkgrnd->yPos_ -= bkgrnd->height_;
	}
}

void CBackground::applyParalaxBackground(int xMove, int yMove) {
	for (background* bkgrnd : backgrounds_) {
		if (bkgrnd->paralaxModifier_ != 0.0) {
			bkgrnd->yPos_ += (yMove * bkgrnd->paralaxModifier_);
			bkgrnd->xPos_ += (xMove * bkgrnd->paralaxModifier_);
		}
	}
}