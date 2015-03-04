#pragma once
#include "Entity.h"
class CCharacter : public CEntity {
	public:
		CCharacter();
		~CCharacter();

	protected:
		int health_;
};

