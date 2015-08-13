#include "glSound.h"

int glSound::getVolume()
{
	return volume;
}

bool glSound::isPlaying()
{
	return Mix_Playing(channel);
}

bool glSound::isPaused()
{
	return Mix_Paused(channel);
}

void glSound::setSound(Mix_Chunk* new_sound)
{
	sound = new_sound;
}

void glSound::stop()
{
	if (Mix_Playing(channel))
	{
		Mix_HaltChannel(channel);
	}
}

void glSound::play()
{
	if (sound == nullptr) return;			// don't play if there is no sound
	stop();									// if there is music playing stop it
	Mix_PlayChannel(channel,sound, loops);	// play the music track
}

void glSound::pause()
{
	if (Mix_Playing(channel))
	{
		Mix_Pause(channel);
	}
}

void glSound::resume()
{
	if (Mix_Paused(channel))
	{
		Mix_Resume(channel);
	}
}

void glSound::setVolume(int new_volume)
{
	if (sound == nullptr) return;
	if (new_volume < 0)						new_volume = 0;
	else if (new_volume > MIX_MAX_VOLUME)	new_volume = MIX_MAX_VOLUME;

	volume = new_volume;

	Mix_VolumeChunk(sound,new_volume);
}