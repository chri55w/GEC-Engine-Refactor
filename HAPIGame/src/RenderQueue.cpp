#include "RenderQueue.h"


//Singleton instance setup
CRenderQueue *CRenderQueue::instance_ = NULL;

CRenderQueue &CRenderQueue::getInstance() {
	if (instance_ == NULL) {
		instance_ = new CRenderQueue();
	}
	return *instance_;
}

CRenderQueue::CRenderQueue() {
	queue_.reserve(50);
}

void CRenderQueue::pushToQueue(std::string spriteName, int x_pos, int y_pos, int frame, int z_index, bool renderAlpha, bool scrolling) {
	renderData* newRenderItem = new renderData(spriteName, x_pos, y_pos, frame, z_index, renderAlpha, scrolling);

	queue_.push_back(newRenderItem);
	
	index_++;

	if (index_ >= (int)queue_.capacity()) {
		queue_.reserve(queue_.capacity() + 5);
	}
}