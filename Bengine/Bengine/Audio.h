#pragma once
#include <SDL_mixer.h>
#include "bengine_typedefs.h"

namespace BG
{
	/* \brief Audio Manager Class
	 * Handles the playing and manipulation of Music and SoundEffect files
	 */
	class Audio
	{

	public:

		/* Plays a sound effect file */
		static void play_sound_effect(SoundEffect* sound_effect, const int &channel, const int &loops, const int &fade_time);

		/* Returns true if the specified channel is currently playing (ignores volume and pause state) */
		static bool channel_playing(const int &channel);

		/* Stop all currently playing sound effects on the specified channel */
		static void stop_channel(const int &channel, const int &fade_time);

		/* Set the pause state of the specified channel */
		static void set_channel_paused(const int &channel, const bool &state);

		/* Returns true if the specified channel is currently paused */
		static bool channel_paused(const int &channel);

		/* Set the volume level sound effect files are played at on the specified channel (0 - 128) */
		static void set_channel_volume(const int &channel, int volume);

		/* Returns the current volume level of the specified channel */
		static int channel_volume(const int &channel);

		/* Plays a music file */
		static void play_music(Music* music, const int &loops, const int &fade_time);

		/* Returns true if music is currently being played (ignores volume and pause state) */
		static bool music_playing();

		/* Stops all currently playing music */
		static void stop_music(const int &fade_time);

		/* Set the pause state of currently playing music */
		static void set_music_paused(const bool &state);

		/* Returns true if music is currently paused */
		static bool music_paused();

		/* Set the volume level music files are played at (0 - 128) */
		static void set_music_volume(int volume);

		/* Returns the current music volume level */
		static int music_volume();

	};
}