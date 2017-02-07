#pragma once
#include <SDL_mixer.h>

namespace BG
{
	class Audio
	{

	public:

		static void playSoundEffect(Mix_Chunk* soundEffect, const int &channel, const int &loops);

		static void playMusic(Mix_Music* music, const int &loops, const int &fadeInMilliseconds);
		static void stopMusic(const int &fadeOutMilliseconds);

		static void setMusicPaused(const bool &state);
		static void setMusicVolume(int volume);

		static bool isMusicPlaying();
		static bool isMusicPaused();
		static int getMusicVolume();

	};
}

