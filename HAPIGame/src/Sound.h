#include "Enum.h"
#include <HAPI_lib.h>

#pragma once
class CSound
{
	public:
		CSound(std::string fileName, CEnum::soundExtension fileType);
		~CSound() {};

		void play(bool loop);
		void stop();

	private:
		CEnum::soundExtension fileType_;
		std::string fileName_;
		int soundID_;
};

