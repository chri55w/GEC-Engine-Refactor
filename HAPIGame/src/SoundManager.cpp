#include "SoundManager.h"
#include <iostream>
#include "Sound.h"

//Singleton instance setup
CSoundManager *CSoundManager::instance_ = NULL;

CSoundManager& CSoundManager::getInstance() {
	if (instance_ == NULL) {
		instance_ = new CSoundManager;
	}
	return *instance_;
}

//Destruction - cleanup of sound map
CSoundManager::~CSoundManager() {
	for (auto sound : sounds_) {
		delete sound.second;
	}
}
//add new sound objects to sound map
void CSoundManager::addSound(std::string filename, CEnum::soundExtension fileType, std::string soundName) {
	CSound *newSound = new CSound(audioLoc + filename, fileType);
	sounds_[soundName] = newSound;
}
//Play previously added sounds (either loaded or streamed media)
void CSoundManager::playSound(std::string soundName, bool loop) {
	if (mute_) {
		return;
	}
	if (sounds_.find(soundName) != sounds_.end()) {
		sounds_[soundName]->play(loop);
	}
}
//Stop previously added sounds (either loaded or streamed media)
void CSoundManager::stopSound(std::string soundName) {
	if (sounds_.find(soundName) != sounds_.end()) {
		sounds_[soundName]->stop();
	}
}
//Stop all sounds that could be playing, this it to ensure all is muted when required.
void CSoundManager::stopAllSound() {
	HAPI->StopStreamedMedia();
	for (auto sound : sounds_) {
		sound.second->stop();
	}
}

//Set the audio to muted, stopping all sounds and preventing all media from being played until audio is unmuted.
void CSoundManager::setMute(bool mute) { 
	mute_ = mute;
	stopAllSound();
}