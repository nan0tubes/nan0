#include "n0/n0.h"

n0AudioManager::n0AudioManager()
{
	pMusic = NULL;
	pMusic = Mix_LoadMUS("07.mp3");
	n0_ASSERT(pMusic, "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
}

n0AudioManager::~n0AudioManager()
{
	Mix_FreeMusic(pMusic);
	pMusic = NULL;
}
