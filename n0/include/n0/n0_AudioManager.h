#ifndef __N0_AUDIOMANAGER_H__
#define __N0_AUDIOMANAGER_H__

class n0AudioManager
{
public:
	
	n0AudioManager();
	virtual ~n0AudioManager();

	// returns hash of filename
	unsigned int LoadMusic(std::string filename);
	// returns hash of filename
	unsigned int LoadEffect(std::string filename);
	// returns hash of filename

	void PlayMusic(std::string filename, int numLoops, int fadeInMs);
	void PlayMusic(unsigned int musicHash, int numLoops, int fadeInMs);
	void PauseMusic(int fadeOutMs);
	void ResumeMusic(int fadeInMs);
	void StopMusic(int fadeOutMs);
	void StartMusic(int fadeInMs); // is this necessary?
	bool IsMusicPlaying();
	unsigned int GetMusicPlayingHash();
	std::string GetMusicPlayingString();

	//TODO: expand effect functionality
	void PlayEffect();
	bool IsEffectPlaying();

private:

	struct SMusic
	{
		int channel;
		unsigned int hash;
		std::string filename;
		Mix_Music * pMusic;

		SMusic() : pMusic(NULL), isPlaying(false) {}
		~SMusic() { Mix_FreeMusic(pMusic); }
	};

	struct SEffect
	{
		bool isPlaying;
		unsigned int hash;
		std::string filename;
		Mix_Chunk * pEffect;

		SEffect() : pEffect(NULL), isPlaying(false) {}
		~SEffect() { Mix_FreeChunk(pEffect); }
	};

	bool bIsInitialized;
	SMusic * pCurrentMusic;

	std::map<unsigned int, SMusic*> listMusic;
	std::map<unsigned int, SEffect*> listEffects;
};

#endif // __N0_AUDIOMANAGER_H__