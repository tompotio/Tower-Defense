#pragma once

#include "assetsmanager.hpp"

class AudioManager
{
	public:
		AudioManager() {
			if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048))
			{
				std::cout << "Mixer Initialization error" << std::endl;
			}
			Mix_VolumeMusic(MIX_MAX_VOLUME);
		}

		~AudioManager() {
			Mix_Quit();
		}

		void PlayMusic(std::string id, AssetManager* assetManager, int loops = 0) {
			Mix_PlayMusic(assetManager->GetMusic(id), loops);
		}

		/* void PauseMusic()
		{
			if (Mix_PlayingMusic() != 0)
				Mix_PausedMusic();
		}

		void ResumeMusic()
		{

			if (Mix_PausedMusic() != 0)
				Mix_ResumeMusic();
		} */

		void PlaySFX(std::string id, AssetManager* assetManager, int loops = 1, int channel = -1)
		{
			Mix_PlayChannel(channel, assetManager->GetSFX(id), loops);
		}

		void sfx_volume(AssetManager* assetManager, int vol) {

			/* std::map<std::string, Mix_Chunk*> allsfx = assetManager->GetAllSFX();
			for (std::map<std::string, Mix_Chunk*>::iterator it = allsfx.begin(); it != allsfx.end(); it++) {
				Mix_VolumeChunk(it->second, vol);

			} */
			/* for (auto const& [key, val] : assetManager->GetAllSFX()) {
				Mix_VolumeChunk(val, vol);
			} */
			for (int i=0; i<=MIX_CHANNELS; i++) {
				Mix_Volume(i, vol);
			}

		}

		void music_volume(int volume) {

			Mix_VolumeMusic(volume);

		}
};
