#include "Audio.h"

void BG::Audio::playSoundEffect(Mix_Chunk* soundEffect, const int& loops)
{
	Mix_PlayChannel(-1, soundEffect, loops);
}

void BG::Audio::playSoundEffect(Mix_Chunk* soundEffect, const int& channel, const int& loops)
{
	Mix_PlayChannel(channel, soundEffect, loops);
}

void BG::Audio::playMusic(Mix_Music* music)
{
	Mix_PlayMusic(music, 0);
}

void BG::Audio::playMusic(Mix_Music* music, const int& loops)
{
	Mix_PlayMusic(music, loops);
}

bool BG::Audio::isMusicPlaying()
{
	return Mix_PlayingMusic();
}

bool BG::Audio::isMusicPaused()
{
	return Mix_PausedMusic();
}

void BG::Audio::pauseMusic()
{
	Mix_PauseMusic();
}

void BG::Audio::resumeMusic()
{
	Mix_ResumeMusic();
}

void BG::Audio::stopMusic()
{
	Mix_HaltMusic();
}
