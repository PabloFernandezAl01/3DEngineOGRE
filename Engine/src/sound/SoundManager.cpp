#include "SoundManager.h"

namespace Sound {

	SoundManager::SoundManager(const ConfigData& data)
	{
		valid = true;
	}

	SoundManager::~SoundManager()
	{

	}

	bool SoundManager::Valid()
	{
		return valid;
	}
}