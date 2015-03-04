#include <iostream>
#include <vector>

#include "Enum.h"

#pragma once
class CBackground
{
public:
	CBackground();
	~CBackground();

	void createBackground(std::string spriteName, float x_pos, float y_pos, int width, int height, bool blitAlpha, CEnum::direction direction_to_scroll = CEnum::DIRECTION_NONE, float scrolling_speed = 0.0);
	void createBackground(std::string spriteName, float x_pos, float y_pos, int width, int height, bool blitAlpha, float paralax_modifier);
	void applyParalaxBackground(int xMove, int yMove);


	private:
		struct background {
			std::string spriteName_;
			float xPos_;
			float yPos_;
			int width_;
			int height_;
			bool blitAlpha_;
			float scrollSpeed_ = 0;
			CEnum::direction moveDir_ = CEnum::direction::DIRECTION_NONE;
			float paralaxModifier_ = 0.0;
		};

		std::vector<background*> backgrounds_;

		void scrollBackground(background* bkgrnd);
		void updateBackgroundLocation(background* bkgrnd, int worldX, int worldY, int screenWidth, int screenHeight);
};

