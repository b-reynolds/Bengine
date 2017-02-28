#include "audio.h"
#include "Logger.h"
#include <string>

/*\
* \brief Plays a sound effect file
* \param soundEffect sound effect file to play
* \param loops amount of times to loop the sound effect (None: 0, Infinite: -1)
* \param fadeInMilliseconds amount of time in milliseconds to fade the sound effect in with (No Fade: 0)
*/
void BG::Audio::play_sound_effect(SoundEffect* sound_effect, const int& channel, const int& loops, const int &fade_time)
{
	Mix_FadeInChannel(channel, sound_effect, loops, fade_time);
	if(fade_time == 0)
	{
		Logger::instance().log(Logger::kDebug, "Playing sound effect on channel " + std::to_string(channel) + " (" + std::to_string(loops) + " loops)");
	}
	else
	{
		Logger::instance().log(Logger::kDebug, "Fading in sound effect on channel (" + std::to_string(fade_time) +
			"ms) (" + std::to_string(channel) + " (" + std::to_string(loops) + " loops)");
	}
}

/**
* \brief Returns true if the specified channel is currently playing (ignores volume and pause state)
*/
bool BG::Audio::channel_playing(const int& channel)
{
	return Mix_Playing(channel);
}

/**
* \brief Stop all currently playing sound effects on the specified channel
* \param fade_time amount of time in milliseconds to fade the music out with (No Fade: 0)
*/
void BG::Audio::stop_channel(const int& channel, const int &fade_time)
{
	Mix_FadeOutChannel(channel, fade_time);
	if (fade_time == 0)
	{
		Logger::instance().log(Logger::kDebug, "Stopped channel " + std::to_string(channel));
	}
	else
	{
		Logger::instance().log(Logger::kDebug, "Fading out channel " + std::to_string(channel) + " (" + std::to_string(fade_time) + "ms)");
	}
}

/**
* \brief Set the pause state of the specified channel
* \param state pause state
*/
void BG::Audio::set_channel_paused(const int &channel, const bool &state)
{
	if (channel_playing(channel))
	{
		state ? Mix_Pause(channel) : Mix_Resume(channel);
		Logger::instance().log(Logger::kDebug, (state ? "Paused" : "Resumed") + std::string(" channel ") + std::to_string(channel));
	}
}

/**
* \brief Returns true if the specified channel is currently paused
*/
bool BG::Audio::channel_paused(const int& channel)
{
	return Mix_Paused(channel);
}

/**
* \brief Set the volume level sound effect files are played at on the specified channel (0 - 128)
* \param volume desired volume level
*/
void BG::Audio::set_channel_volume(const int& channel, int volume)
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
	Logger::instance().log(Logger::kDebug, "Set channel " + std::to_string(channel) + "'s volume to" + std::to_string(volume));
}

/**
* \brief Returns the current volume level of the specified channel
*/
int BG::Audio::channel_volume(const int& channel)
{
	return Mix_Volume(channel, -1);
}

/**
* \brief Plays a music file
* \param music music file to play
* \param loops amount of times to loop the music (None: 0, Infinite: -1)
* \param fade_time amount of time in milliseconds to fade the music in with (No Fade: 0)
*/
void BG::Audio::play_music(Music* music, const int& loops, const int& fade_time)
{
	Mix_FadeInMusic(music, loops, fade_time);
	if (fade_time == 0)
	{
		Logger::instance().log(Logger::kDebug, "Playing music");
	}
	else
	{
		Logger::instance().log(Logger::kDebug, "Fading in music (" + std::to_string(fade_time) + "ms)");
	}
}

/**
* \brief Returns true if music is currently being played (ignores volume and pause state)
*/
bool BG::Audio::music_playing()
{
	return Mix_PlayingMusic();
}

/**
* \brief Stops all currently playing music
* \param fade_time amount of time in milliseconds to fade the music out with (No Fade: 0)
*/
void BG::Audio::stop_music(const int &fade_time)
{
	if (fade_time > 0)
	{
		Mix_FadeOutMusic(fade_time);
		Logger::instance().log(Logger::kDebug, "Fading out music (" + std::to_string(fade_time) + "ms)");
	}
	else
	{
		Mix_HaltMusic();
		Logger::instance().log(Logger::kDebug, "Stopped music");
	}
}

/**
* \brief Set the pause state of currently playing music
* \param state pause state
*/
void BG::Audio::set_music_paused(const bool& state)
{
	if (music_playing())
	{
		state ? Mix_PauseMusic() : Mix_ResumeMusic();
		Logger::instance().log(Logger::kDebug, (state ? "Paused" : "Resumed") + std::string(" music"));
	}
}

/** 
* \brief Returns true if music is currently paused
*/
bool BG::Audio::music_paused()
{
	return Mix_PausedMusic();
}

/**
* \brief Set the volume level music files are played at (0 - 128)
* \param volume desired volume level
*/
void BG::Audio::set_music_volume(int volume)
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
	Logger::instance().log(Logger::kDebug, "Set music volume to " + std::to_string(volume));
}

/**
* \brief Returns the current music volume level
*/
int BG::Audio::music_volume()
{
	return Mix_VolumeMusic(-1);
}