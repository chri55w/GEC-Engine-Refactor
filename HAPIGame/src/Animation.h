#include <vector>
#include <unordered_map>
#include <HAPI_lib.h>


#pragma once
class CAnimation {
public:
	CAnimation();
	~CAnimation();

	int newAnimation(std::vector<int> spriteSequence);
	int newAnimation(std::vector<int> spriteSequence, int id);

	void setFrameRate(int fps) { frameRate = fps; }

	int updateFrame(int id, int &currFrame);

	int getFrame(int id, int currFrame);

	private:
		struct animationSeq {
			std::vector<int> frameSeq;
			int nextAnimID = -1;

			animationSeq( std::vector<int> seq) : frameSeq(seq) {}
			animationSeq( std::vector<int> seq, int nextID) : frameSeq(seq), nextAnimID(nextID) {}
		};
	std::vector<animationSeq*> animations;
	unsigned int frameRate = 1;
	
	DWORD time = HAPI->GetTime();

};

