#pragma once

#include "game.hpp"

class AudioManager
{
	AudioManager()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096 < 0))
		{
			std::cout << "Mixer Initialization error" << std::endl;
		}
	};

	~AudioManager()
	{
		Mix_Quit();
	}

	void PlayMusic(std::string filename,AssetManager* assetManager, int loops = -1)
	{
		Mix_PlayMusic(assetManager->GetMusic(filename), loops);
	}

	void PauseMusic()
	{
		if (Mix_PlayingMusic() != 0)
			Mix_PausedMusic();
	}

	void ResumeMusic()
	{

		if (Mix_PausedMusic() != 0)
			Mix_ResumeMusic();
	}

	void PlaySFX(std::string filename,AssetManager* assetManager, int loops = 0, int channel = 0)
	{
		Mix_PlayChannel(channel, assetManager->GetSFX(filename), loops);
	}
};

