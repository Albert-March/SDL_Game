#pragma once
#include "SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <cassert>

#define AM AudioManager::GetInstance()

class AudioManager
{
private:
	std::unordered_map<std::string, Mix_Chunk*> _clips;
	std::unordered_map<std::string, Mix_Music*> _songs;

	bool _muted = false;
	int _previousMusicVolume = MIX_MAX_VOLUME;
	int _previousSFXVolume = MIX_MAX_VOLUME;

	AudioManager()
	{
		int result = Mix_OpenAudio(
			44100,                //Standard frequency that works on most systems
			MIX_DEFAULT_FORMAT,   //Default sample format
			2,                    //Number of hardware channels (2 -> stereo)
			2048                  //Sample (chunk) size -> avoid lag
		);

		bool succes = result >= 0;

		if (!succes)
			throw SDL_GetError();
	}

	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

public:
	inline static AudioManager& GetInstance()
	{
		static AudioManager am;
		return am;
	}

	inline void LoadClip(std::string name)
	{
		assert(_clips.find(name) == _clips.end());

		Mix_Chunk* loadedChunk = Mix_LoadWAV(("resources/audio/sfx/" + name + ".wav").c_str());

		assert(loadedChunk != nullptr);

		_clips.emplace(name, loadedChunk);
	}

	inline void LoadSong(std::string name)
	{
		assert(_songs.find(name) == _songs.end());

		Mix_Music* loadedMusic = Mix_LoadMUS(("resources/audio/music/" + name + ".mp3").c_str());

		assert(loadedMusic != nullptr);

		_songs.emplace(name, loadedMusic);
	}

	inline void PlayClip(std::string name, int repetitions)
	{
		assert(_clips.find(name) != _clips.end());

		Mix_PlayChannel(-1, _clips[name], repetitions);
	}

	inline void PlaySong(std::string name)
	{
		assert(_songs.find(name) != _songs.end());

		Mix_FadeInMusic(_songs[name], -1, 200);
	}

	inline void Mute()
	{
		if (!_muted) {
			_muted = true;
			_previousMusicVolume = Mix_VolumeMusic(-1);
			_previousSFXVolume = Mix_Volume(-1, -1);
			Mix_VolumeMusic(0);				//Mutea Musica
			Mix_Volume(-1, 0);				//Mutea efectos de sonido
		}
	}

	inline void Unmute()
	{
		if (_muted) {
			_muted = false;
			Mix_VolumeMusic(_previousMusicVolume);
			Mix_Volume(-1, _previousSFXVolume);
		}
	}

	inline bool GetMuted() { return _muted; }

	inline void StopAudio()
	{
		Mix_HaltMusic();
		Mix_HaltChannel(-1);
	}

	inline void SetMusicVolume(int volume) {
		if (volume < 0) {
			volume = 0;
		}
		else if (volume > MIX_MAX_VOLUME) {
			volume = MIX_MAX_VOLUME;
		}

		Mix_VolumeMusic(volume);
	}

	inline void SetSFXVolume(int volume) {
		if (volume < 0) {
			volume = 0;
		}
		else if (volume > MIX_MAX_VOLUME) {
			volume = MIX_MAX_VOLUME;
		}

		Mix_Volume(-1, volume); //-1 Tots els canals de VFX
	}

};