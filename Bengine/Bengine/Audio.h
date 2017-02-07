#pragma once
#include <SDL_mixer.h>

namespace BG
{
	class Audio
	{

	public:

		static void playSoundEffect(Mix_Chunk* soundEffect, const int &channel, const int &loops, const int &fadeInMilliseconds);
		static void stopChannel(const int &channel, const int &fadeOutMilliseconds);

		static void playMusic(Mix_Music* music, const int &loops, const int &fadeInMilliseconds);
		static void stopMusic(const int &fadeOutMilliseconds);

		static void setChannelPaused(const int &channel, const bool &state);
		static void setMusicPaused(const bool &state);

		static void setChannelVolume(const int &channel, int volume);
		static void setMusicVolume(int volume);

		static bool isChannelPlaying(const int &channel);
		static bool isMusicPlaying();

		static bool isChannelPaused(const int &channel);
		static bool isMusicPaused();

		static int getChannelVolume(const int &channel);
		static int getMusicVolume();

	};
}

