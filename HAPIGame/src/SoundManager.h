#include "Enum.h"
#include <unordered_map>

#pragma once
class CSound;
class CSoundManager
{
	public:
		static CSoundManager & getInstance();
		~CSoundManager();

		void addSound(std::string filename, CEnum::soundExtension fileType, std::string soundName);

		void playSound(std::string soundName, bool loop = false);

		void stopSound(std::string soundName);
		void stopAllSound();
		bool getMuted() const { return mute_; }
		void setMute(bool mute);

	protected:
		CSoundManager() {};

	private:
		static CSoundManager* instance_;
		std::unordered_map<std::string, CSound*> sounds_;

		std::string audioLoc = "Media/";

		bool mute_ = false;
};

#define AUDIO CSoundManager::getInstance()

