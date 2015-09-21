#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "AssetManager.h"
#include "GameData.h"
#include "general.h"
#include "utils/LinkedList.h"

struct MusicHandle
{
    Node<MusicHandle*>*     node = nullptr;
    sf::Music               music;

    void play()
    {
        music.play();
    }

    void stop()
    {
        music.stop();
    }

    void pause()
    {
        music.pause();
    }

    void loop(bool loop)
    {
        music.setLoop(loop);
    }

    void volume(float volume)
    {
        music.setVolume(volume);
    }

    bool isFinished()
    {
        return (music.getStatus() == sf::Music::Stopped);
    }
};

struct SoundHandle
{
    Node<SoundHandle*>*     node = nullptr;
    sf::Sound               sound;

    void play()
    {
        sound.play();
    }

    void stop()
    {
        sound.stop();
    }

    void pause()
    {
        sound.pause();
    }

    void loop(bool loop)
    {
        sound.setLoop(loop);
    }

    void volume(float volume)
    {
        sound.setVolume(volume);
    }

    bool isFinished()
    {
        return (sound.getStatus() == sf::Sound::Stopped);
    }
};

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

        SoundHandle* addSound(string name, bool destroy_old = false);
        MusicHandle* addMusic(string name, bool destroy_old = false);

        void freeResources();

        //
        void updateVolumeSFX();
        void updateVolumeMusic();
    protected:
        LinkedList<SoundHandle*>    unused_sound;
        LinkedList<MusicHandle*>    unused_music;

        LinkedList<SoundHandle*>    sfx_temp;      // sfx that will be automatically deleted when finished
        LinkedList<SoundHandle*>    sfx_perm;

        LinkedList<MusicHandle*>    music_temp;    // music that will be automatically deleted when finished
        LinkedList<MusicHandle*>    music_perm;

        void removeTempSound();
        void removeTempMusic();
};

#endif // AUDIOMANAGER_H
