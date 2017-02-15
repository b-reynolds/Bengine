#pragma once
#include <SDL_mixer.h>
#include "Bengine.h"

namespace BG
{
	/* \brief Audio Manager Class
	 * Handles the playing and manipulation of Music and SoundEffect files
	 */
	class Audio
	{

	public:

		/* Plays a sound effect file */
		static void playSoundEffect(SoundEffect* soundEffect, const int &channel, const int &loops, const int &fadeInMilliseconds);

		/* Returns true if the specified channel is currently playing (ignores volume and pause state) */
		static bool isChannelPlaying(const int &channel);

		/* Stop all currently playing sound effects on the specified channel */
		static void stopChannel(const int &channel, const int &fadeOutMilliseconds);

		/* Set the pause state of the specified channel */
		static void setChannelPaused(const int &channel, const bool &state);

		/* Returns true if the specified channel is currently paused */
		static bool getChannelPaused(const int &channel);

		/* Set the volume level sound effect files are played at on the specified channel (0 - 128) */
		static void setChannelVolume(const int &channel, int volume);

		/* Returns the current volume level of the specified channel */
		static int getChannelVolume(const int &channel);

		/* Plays a music file */
		static void playMusic(Music* music, const int &loops, const int &fadeInMilliseconds);

		/* Returns true if music is currently being played (ignores volume and pause state) */
		static bool isMusicPlaying();

		/* Stops all currently playing music */
		static void stopMusic(const int &fadeOutMilliseconds);

		/* Set the pause state of currently playing music */
		static void setMusicPaused(const bool &state);

		/* Returns true if music is currently paused */
		static bool getMusicPaused();

		/* Set the volume level music files are played at (0 - 128) */
		static void setMusicVolume(int volume);

		/* Returns the current music volume level */
		static int getMusicVolume();

	};
}