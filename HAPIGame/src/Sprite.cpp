#include "Sprite.h"

//construct a sprite object
CSprite::CSprite(CRectangle spriteSize, CRectangle spriteFrameSize) {
	*sprite_rect_ = spriteSize;
	*frameSize_ = spriteFrameSize;
	animFrames_ = spriteSize.height() / spriteFrameSize.height();
}
//destroy a sprite object and any dynamicly allocated memory
CSprite::~CSprite() {
	delete[] spritePtr_;
	delete sprite_rect_;
	delete frameSize_;
}
//load a new sprite
bool CSprite::loadSprite(std::string fileLoc) {
	if (!HAPI->LoadTexture(fileLoc, &spritePtr_)) {
		return false;
	}
	return true;
}
//render this sprite using either blit or alphablit
void CSprite::renderSprite(BYTE *screenPtr, const CRectangle &dest_rect, int x_pos, int y_pos, int frame, bool blitAlpha) {
	if (blitAlpha) {
		alphaBlitSprite(screenPtr, dest_rect, x_pos, y_pos, frame);
	} else {
		blitSprite(screenPtr, dest_rect, x_pos, y_pos, frame);
	}
}
//alpha blit for this sprite
void CSprite::alphaBlitSprite(BYTE *screenPtr, const CRectangle &dest_rect, int x_pos, int y_pos, int frame) {
	int sprite_width = sprite_rect_->width();
	int dest_width = dest_rect.width();

	int source_y = frameSize_->height() * (frame);
	//Create and translate clipped rectangle object
	CRectangle clipped_rect(*sprite_rect_);
	clipped_rect.clipTo(*frameSize_);
	clipped_rect.translate(x_pos, y_pos);

	//Check if rectangle is completely outside destination rectangle
	if (clipped_rect.completelyOutside(dest_rect)) {
		return;
	}
	//Check if rectangle is only partially inside (needs clipping)
	if (clipped_rect.partiallyInside(dest_rect)) {
		//Clip rectangle to destination rectangle
		clipped_rect.clipTo(dest_rect);
		//Translate rectangle back
		clipped_rect.translate(-x_pos, -y_pos);
		//Clamp x and y values to prevent negative values
		if (x_pos < 0) {
			x_pos = 0;
		}
		if (y_pos < 0) {
			y_pos = 0;
		}
	} else {
		//If completely onscreen then just translate rectangle back
		clipped_rect.translate(-x_pos, -y_pos);
	}

	//Clipped height and width
	int clipped_height = clipped_rect.height();
	int clipped_width = clipped_rect.width();

	//Declare Pointers and offsets for quick access
	BYTE *p_dest = screenPtr + (x_pos + y_pos * dest_width) * 4;
	BYTE *p_source = spritePtr_ + ((source_y * sprite_width) * 4) + clipped_rect.getOffset(sprite_width) * 4;

	int destLineOffset = (dest_width - clipped_width) * 4;
	int srcLineOffset = (sprite_width - clipped_width) * 4;


	//Blit to screen
	for (int y = 0; y < clipped_height; y++) {
		for (int x = 0; x < clipped_width; x++) {
			BYTE blue = p_source[0];
			BYTE green = p_source[1];
			BYTE red = p_source[2];
			BYTE alpha = p_source[3];

			//Do nothing if alpha channel = 0
			if (alpha != 0) {
				//Dont calculate modification if alpha channel = 255
				if (alpha != 255) {
					blue = p_dest[0] + ((alpha * (blue - p_dest[0])) >> 8);
					green = p_dest[1] + ((alpha * (green - p_dest[1])) >> 8);
					red = p_dest[2] + ((alpha * (red - p_dest[2])) >> 8);
				}
				//Apply colour channels to screen
				p_dest[0] = blue;
				p_dest[1] = green;
				p_dest[2] = red;
				p_dest[3] = alpha;
			}
			//Push pointer to next pixel
			p_source += 4;
			p_dest += 4;
		}
		//Skip to first pixel on next line
		p_dest += destLineOffset;
		p_source += srcLineOffset;
	}
}
//standard clip blit for this sprite
void CSprite::blitSprite(BYTE *screenPtr, const CRectangle &dest_rect, int x_pos, int y_pos, int frame) {
	int sprite_width = sprite_rect_->width();
	int dest_width = dest_rect.width();

	int source_y = frameSize_->height() * (frame);
	//Create and translate clipped rectangle object
	CRectangle clipped_rect(*sprite_rect_);
	clipped_rect.clipTo(*frameSize_);
	clipped_rect.translate(x_pos, y_pos);

	//Check if rectangle is completely outside destination rectangle
	if (clipped_rect.completelyOutside(dest_rect)) {
		return;
	}
	//Check if rectangle is only partially inside (needs clipping)
	if (clipped_rect.partiallyInside(dest_rect)) {
		//Clip rectangle to destination rectangle
		clipped_rect.clipTo(dest_rect);
		//Translate rectangle back
		clipped_rect.translate(-x_pos, -y_pos);
		//Clamp x and y values to prevent negative values
		if (x_pos < 0) {
			x_pos = 0;
		}
		if (y_pos < 0) {
			y_pos = 0;
		}
	} else {
		//If completely onscreen then just translate rectangle back
		clipped_rect.translate(-x_pos, -y_pos);
	}

	//Clipped height and width
	int clipped_height = clipped_rect.height();
	int clipped_width = clipped_rect.width();

	//Declare Pointers and offsets for quick access
	BYTE *p_dest = screenPtr + (x_pos + y_pos * dest_width) * 4;
	BYTE *p_source = spritePtr_ + ((source_y * sprite_width) * 4) + clipped_rect.getOffset(sprite_width) * 4;

	int destLineOffset = (dest_width - clipped_width) * 4;
	int srcLineOffset = (sprite_width - clipped_width) * 4;


	//Blit to screen
	for (int y = 0; y < clipped_height; y++) {
		for (int x = 0; x < clipped_width; x++) {
			BYTE blue = p_source[0];
			BYTE green = p_source[1];
			BYTE red = p_source[2];

			//Apply colour channels to screen
			p_dest[0] = blue;
			p_dest[1] = green;
			p_dest[2] = red;

			//Push pointer to next pixel
			p_source += 4;
			p_dest += 4;
		}
		//Skip to first pixel on next line
		p_dest += destLineOffset;
		p_source += srcLineOffset;
	}

}