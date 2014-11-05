#ifndef __N0_AUDIOMANAGER_H__
#define __N0_AUDIOMANAGER_H__

class n0AudioManager
{
public:
	n0AudioManager();
	virtual ~n0AudioManager();

	Mix_Music * pMusic;
};

#endif // __N0_AUDIOMANAGER_H__