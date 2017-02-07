#pragma once
#include <SDL_mixer.h>

namespace BG
{
	class Audio
	{

	public:

		const int INFINITE = -1;

		static void playSoundEffect(Mix_Chunk* soundEffect, const int &channel);
		static void playSoundEffect(Mix_Chunk* soundEffect, const int &channel, const int &loops);

		static void playMusic(Mix_Music* music);
		static void playMusic(Mix_Music* music, const int &loops);

		static bool isMusicPlaying();
		static bool isMusicPaused();
		static void pauseMusic();
		static void resumeMusic();
		static void stopMusic();

	};
}

