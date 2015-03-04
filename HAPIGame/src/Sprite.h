#include "visualisation.h"
#include "Rectangle.h"

#pragma once
class CSprite {
	public:
		CSprite(CRectangle spriteSize, CRectangle spriteFrameSize);
		~CSprite();
		bool loadSprite(std::string fileLoc);
		void renderSprite(BYTE *screenPtr, const CRectangle &dest_rect, int x_pos, int y_pos, int frame, bool alphaBlit);

		int getSpriteFrameWidth() const { return frameSize_->width(); }
		int getSpriteFrameHeight() const { return frameSize_->height(); }

		BYTE* getSpritePtr() const { return spritePtr_; }

	private:
		void alphaBlitSprite(BYTE *screenPtr, const CRectangle &dest_rect, int x_pos, int y_pos, int frame);
		void blitSprite(BYTE *screenPtr, const CRectangle &dest_rect, int x_pos, int y_pos, int frame);
		CRectangle *sprite_rect_ =  new CRectangle(0, 0, 0, 0);
		BYTE *spritePtr_ = nullptr;
		CRectangle *frameSize_ = new CRectangle(0,0,0,0);
		int animFrames_ = 0;

		int rendError_ = 0;
};

