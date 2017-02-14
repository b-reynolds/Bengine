#include "Audio.h"

/*\
* \brief Plays a sound effect file
* \param soundEffect sound effect file to play
* \param loops amount of times to loop the sound effect (None: 0, Infinite: -1)
* \param fadeInMilliseconds amount of time in milliseconds to fade the sound effect in with (No Fade: 0)
*/
void BG::Audio::playSoundEffect(SoundEffect* soundEffect, const int& channel, const int& loops, const int &fadeInMilliseconds)
{
	Mix_FadeInChannel(channel, soundEffect, loops, fadeInMilliseconds);
}

/**
* \brief Returns true if the specified channel is currently playing (ignores volume and pause state)
*/
bool BG::Audio::isChannelPlaying(const int& channel)
{
	return Mix_Playing(channel);
}

/**
* \brief Stop all currently playing sound effects on the specified channel
* \param fadeOutMilliseconds amount of time in milliseconds to fade the music out with (No Fade: 0)
*/
void BG::Audio::stopChannel(const int& channel, const int &fadeOutMilliseconds)
{
	Mix_FadeOutChannel(channel, fadeOutMilliseconds);
}

/**
* \brief Set the pause state of the specified channel
* \param state pause state
*/
void BG::Audio::setChannelPaused(const int &channel, const bool &state)
{
	if (isChannelPlaying(channel))
	{
		state ? Mix_Pause(channel) : Mix_Resume(channel);
	}
}

/**
* \brief Returns true if the specified channel is currently paused
*/
bool BG::Audio::getChannelPaused(const int& channel)
{
	return Mix_Paused(channel);
}

/**
* \brief Set the volume level sound effect files are played at on the specified channel (0 - 128)
* \param volume desired volume level
*/
void BG::Audio::setChannelVolume(const int& channel, int volume)
{
	if (volume > MIX_MAX_VOLUME)
	{
		volume = MIX_MAX_VOLUME;
	}
	else if (volume < 0)
	{
		volume = 0;
	}
	Mix_Volume(channel, volume);
}

/**
* \brief Returns the current volume level of the specified channel
*/
int BG::Audio::getChannelVolume(const int& channel)
{
	return Mix_Volume(channel, -1);
}

/**
* \brief Plays a music file
* \param music music file to play
* \param loops amount of times to loop the music (None: 0, Infinite: -1)
* \param fadeInMilliseconds amount of time in milliseconds to fade the music in with (No Fade: 0)
*/
void BG::Audio::playMusic(Music* music, const int& loops, const int& fadeInMilliseconds)
{
	Mix_FadeInMusic(music, loops, fadeInMilliseconds);
}

/**
* \brief Returns true if music is currently being played (ignores volume and pause state)
*/
bool BG::Audio::isMusicPlaying()
{
	return Mix_PlayingMusic();
}

/**
* \brief Stops all currently playing music
* \param fadeOutMilliseconds amount of time in milliseconds to fade the music out with (No Fade: 0)
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
* \brief Set the pause state of currently playing music
* \param state pause state
*/
void BG::Audio::setMusicPaused(const bool& state)
{
	if (isMusicPlaying())
	{
		state ? Mix_PauseMusic() : Mix_ResumeMusic();
	}
}

/**
* \brief Returns true if music is currently paused
*/
bool BG::Audio::getMusicPaused()
{
	return Mix_PausedMusic();
}

/**
* \brief Set the volume level music files are played at (0 - 128)
* \param volume desired volume level
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
* \brief Returns the current music volume level
*/
int BG::Audio::getMusicVolume()
{
	return Mix_VolumeMusic(-1);
}