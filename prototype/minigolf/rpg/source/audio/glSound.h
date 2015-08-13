#ifndef GLSOUND_H_INCLUDED
#define GLSOUND_H_INCLUDED

#include "general.h"

class glSound
{

	public :
		virtual void setSound(Mix_Chunk* new_sound);
		virtual void play();
		virtual void pause();
		virtual void resume();
		virtual void stop();
		virtual void setVolume(int new_volume);

		int getVolume();
		bool isPlaying();
		bool isPaused();

		int channel = -1;
		int loops = 1;

	protected:
		int volume = MIX_MAX_VOLUME;
		Mix_Chunk* sound = nullptr;
};

#endif // GLSOUND_H
