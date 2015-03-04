#include "Animation.h"

//Animation handler construction, generate a default animation with frame 0;
CAnimation::CAnimation() {
	animationSeq *defaultAnim = new animationSeq(std::vector < int > {0});
	animations.push_back(defaultAnim);
}
//Animation handler destruction, delete all stored animations and data 
CAnimation::~CAnimation()
{
	for (auto anim : animations) {
		delete anim;
	}
}
//Create a new animation using the provided sequence of frames, this returns an int id to be stored and later accessed by the corresponding entity.
int CAnimation::newAnimation(std::vector<int> spriteSequence) {
	animationSeq *newAnim = new animationSeq(spriteSequence);
	animations.push_back(newAnim);

	return (int)animations.size()-1;
}
//Create a new animation using the provided sequence of frames and a next animation ID, this returns an int id to be stored and later accessed by the corresponding entity. 
//the next anim id should provide the entity with the opportunity to progress onto the next stage of an animation
int CAnimation::newAnimation(std::vector<int> spriteSequence, int id) {
	if (id < (int)animations.size() && id > 0) {
		animationSeq *newAnim = new animationSeq(spriteSequence, id);
		animations.push_back(newAnim);
	} else {
		animationSeq *newAnim = new animationSeq(spriteSequence);
		animations.push_back(newAnim);
		HAPI->UserMessage("Error: Next Animation Not Found for id '" + std::to_string(id) + "'", "Error - Animation");
	}
	return (int)animations.size() - 1;
}
//update an animation using the current frame and id passing back the frame id so should there be any change id as well the new animation would be processed
int CAnimation::updateFrame(int id, int &currFrame) {
	if (HAPI->GetTime() - time > (1000 / frameRate)) {
		if (currFrame < (int)animations[id]->frameSeq.size() - 1) {
			currFrame++;
		} else {
			if (animations[id]->nextAnimID == -1) {
				currFrame = 0;
			} else {
				id = animations[id]->nextAnimID;
			}
		}
		time = HAPI->GetTime();
	}
	return id;
}
//get the current frame using the animation id and the current frame of that animation.
int CAnimation::getFrame(int id, int currFrame) {
	if (id < (int)animations.size()) {
		if (currFrame < (int)animations[id]->frameSeq.size()) {
			return animations[id]->frameSeq[currFrame];
		}
	} 
	return 0;
}