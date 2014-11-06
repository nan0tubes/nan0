#include "n0/n0.h"

n0AudioManager::n0AudioManager()
	: bIsInitialized(false)
{
	// Init SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		n0_ASSERT(false, "SDL could not initialize! SDL Error: %s\v", SDL_GetError());
		return;
	}
	// Init SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		n0_ASSERT(false, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}

	bIsInitialized = true;
}

n0AudioManager::~n0AudioManager()
{
	for (unsigned int i = 0; i < listMusic.size(); ++i)
	{
		delete listMusic.at(i);
		listMusic.at(i) = NULL;
	}
	listMusic.clear();

	for (unsigned int i = 0; i < listEffects.size(); ++i)
	{
		delete listEffects.at(i);
		listEffects.at(i) = NULL;
	}
	listEffects.clear();
}
