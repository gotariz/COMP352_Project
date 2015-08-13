#ifndef GLMUSIC_INCLUDED
#define GLMUSIC_INCLUDED

#include "general.h"

class glMusic
{
	public:
		virtual void setTrack(Mix_Music* new_track);
		virtual void play();
		virtual void pause();
		virtual void resume();
		virtual void stop();
		virtual void setVolume(int new_volume);

		int getVolume();
		bool isPlaying();
		bool isPaused();
		
		int loops = 1;
	protected:
		int volume = MIX_MAX_VOLUME;
		Mix_Music* track = nullptr;
};

#endif //GLMUSIC_INCLUDED