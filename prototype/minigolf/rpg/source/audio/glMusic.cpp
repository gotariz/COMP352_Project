#include "glMusic.h"

int glMusic::getVolume()
{
	return volume;
}

bool glMusic::isPlaying()
{
	return Mix_PlayingMusic();
}

bool glMusic::isPaused()
{
	return Mix_PausedMusic();
}

void glMusic::setTrack(Mix_Music* new_track)
{
	track = new_track;
}

void glMusic::stop()
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}
}

void glMusic::play()
{
	if (track == nullptr) return;	// don't play if there is no music
	stop();							// if there is music playing stop it
	Mix_PlayMusic(track, loops);		// play the music track
}

void glMusic::pause()
{
	if (Mix_PlayingMusic())
	{
		Mix_PauseMusic();
	}
}

void glMusic::resume()
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void glMusic::setVolume(int new_volume)
{
	if (new_volume < 0)						new_volume = 0;
	else if (new_volume > MIX_MAX_VOLUME)	new_volume = MIX_MAX_VOLUME;

	volume = new_volume;

	Mix_VolumeMusic(new_volume);
}
