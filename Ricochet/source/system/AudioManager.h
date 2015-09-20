#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "AssetManager.h"
#include "GameData.h"
#include "general.h"
#include "utils/LinkedList.h"

class AudioManager
{
    public:
        AudioManager();
        virtual ~AudioManager();

        void update();

        int max_sounds = 128;   // according to sfml should never exceed 256

        int volume_sfx = 100;
        int volume_music = 100;

        void playSound(string name, bool destroy_old = false);
        void playMusic(string name, bool destroy_old = false);

        sf::Sound* addSound(string name);
        sf::Music* addMusic(string name);

        void freeResources();

        //
        void updateVolumeSFX();
        void updateVolumeMusic();
    protected:
        LinkedList<sf::Sound*>  unused_sound;
        LinkedList<sf::Music*>  unused_music;



        LinkedList<sf::Sound*> sfx_temp;      // sfx that will be automatically deleted when finished
        LinkedList<sf::Music*> music_temp;    // music that will be automatically deleted when finished

        vector<sf::Sound*> sfx_perm;      // sfx that lasts until it is removed
        vector<sf::Music*> music_perm;    // music that lasts until it is removed

};

#endif // AUDIOMANAGER_H
