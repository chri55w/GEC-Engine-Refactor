#include <iostream>
#include <vector>

#pragma once

class CRenderQueue {
	public:
		static CRenderQueue &getInstance();
		struct renderData {
			std::string spriteName;
			int xPos;
			int yPos;
			int frame;
			int zIndex;
			bool renderAlpha;
			bool scrolling;
			renderData(std::string sprite_name, int x_pos, int y_pos, int _frame, int z_index, bool _renderAlpha, bool _scrolling) : spriteName(sprite_name), xPos(x_pos), yPos(y_pos), frame(_frame), zIndex(z_index), renderAlpha(_renderAlpha), scrolling(_scrolling) {};
		};
		void pushToQueue(std::string spriteName, int x_pos, int y_pos, int frame, int z_index, bool renderAlpha = false, bool scrolling = false);
		void setRenderCapacity(int newCapacity) { queue_.reserve(newCapacity); }
		

	protected:
		CRenderQueue();


	private:
		static CRenderQueue *instance_;
		std::vector<renderData*> queue_;
		int index_ = 0;
};

#define RENDERQUEUE CRenderQueue::getInstance()

