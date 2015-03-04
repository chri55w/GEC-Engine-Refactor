#include "Sound.h"

//Construct a sound object consisting of a filename and file type for processing upon play call
CSound::CSound(std::string fileName, CEnum::soundExtension fileType) {
	fileType_ = fileType;
	fileName_ = fileName;
	if (fileType_ == CEnum::WAV) {
		HAPI->LoadSound(fileName, &soundID_);
	}
}

//Play sound from sound map, if filetype enum is WAV use playasound function else use the stored filename to play streamed media
void CSound::play( bool loop) {
	if (fileType_ == CEnum::WAV) {
		HAPI->PlayASound(soundID_, loop);
	} else {
		HAPI->PlayStreamedMedia(fileName_);
	}
}

//Stop sound from sound map, if filetype enum is WAV use stopsound function else use the stop streamed media function
void CSound::stop() {
	if (fileType_ == CEnum::WAV) {
		HAPI->StopSound(soundID_);
	} else {
		HAPI->StopStreamedMedia();
	}
}