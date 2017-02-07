#include "Audio.h"

void BG::Audio::playSoundEffect(Mix_Chunk* soundEffect, const int& channel, const int& loops)
{
	Mix_PlayChannel(channel, soundEffect, loops);
}

/**
* @brief Play a music file
* @param music The music file to play
* @param loops The amount of times to loop the music (None: 0, Infinite: -1)
* @param fadeInMilliseconds The amount of time in milliseconds to fade the music in with (No Fade: 0)
*/
void BG::Audio::playMusic(Mix_Music* music, const int& loops, const int& fadeInMilliseconds)
{
	Mix_FadeInMusic(music, loops, fadeInMilliseconds);
}

/**
* @brief Stop all currently playing music
* @param fadeOutMilliseconds The amount of time in milliseconds to fade the music out with (No Fade: 0)
*/
void BG::Audio::stopMusic(const int &fadeOutMilliseconds)
{
	if (fadeOutMilliseconds > 0)
	{
		Mix_FadeOutMusic(fadeOutMilliseconds);
	}
	else
	{
		Mix_HaltMusic();
	}
}


/**
* @brief Set the volume level music files are played at (0 - 128)
* @param volume Desired volume level
*/
void BG::Audio::setMusicVolume(int volume)
{
	if (volume > MIX_MAX_VOLUME)
	{
		volume = MIX_MAX_VOLUME;
	}
	else if (volume < 0)
	{
		volume = 0;
	}
	Mix_VolumeMusic(volume);
}

/**
* @brief Set the pause state of currently playing music
* @param state Paused: True, Playing: False
*/
void BG::Audio::setMusicPaused(const bool& state)
{
	if (isMusicPlaying())
	{
		state ? Mix_PauseMusic() : Mix_ResumeMusic();
	}
}

/**
* @brief Returns true if music is currently being played (ignores volume and pause state)
*/
bool BG::Audio::isMusicPlaying()
{
	return Mix_PlayingMusic();
}

/**
* @brief Returns true if music is currently paused
*/
bool BG::Audio::isMusicPaused()
{
	return Mix_PausedMusic();
}

/**
* @brief Returns the current music volume level
*/
int BG::Audio::getMusicVolume()
{
	return Mix_VolumeMusic(-1);
}