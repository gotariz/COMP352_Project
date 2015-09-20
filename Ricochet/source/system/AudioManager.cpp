#include "AudioManager.h"

AudioManager::AudioManager()
{
    //ctor
}

AudioManager::~AudioManager()
{
    //dtor
}

void AudioManager::update()
{

    Node<sf::Sound*>* node = sfx_temp.getRoot();
    Node<sf::Sound*>* next = nullptr;

    while (node)
    {
        next = node->next;
        if (node->data->getStatus() == sf::Sound::Status::Stopped)
        {
            unused_sound.add(node->data);
            sfx_temp.remove(node);
        }
        node = next;
    }
}

void AudioManager::playSound(string name, bool destroy_old)
{
    // check number of sounds
    int total_sounds = sfx_temp.getSize() + music_temp.getSize();

    // if max decide to destroy old sound or not
    if (total_sounds >= max_sounds && destroy_old)
    {
        if (sfx_temp.getSize() == 0) return; // no sounds to recycle so cannot play the new sound

        // destroy the old sound and add it to the recycled
        sf::Sound* recycled_sound = sfx_temp.getRoot()->data;
        recycled_sound->stop();

        sfx_temp.remove(sfx_temp.getRoot());
        unused_sound.add(recycled_sound);
    }
    else if (total_sounds >= max_sounds)
    {
        return; // not going to play the sound
    }

    // if not max create new sound or recycle expired
    sf::Sound* sound = nullptr;
    if (unused_sound.getSize() > 0)
    {
        sound = unused_sound.getLast()->data;
        unused_sound.remove(unused_sound.getLast());
    }
    else
    {
        cout << "creating sound" << endl;
        sound = new sf::Sound();
    }

    // set sound properties
    sf::SoundBuffer* buffer = gdata.assets->getSound(name);

    if (buffer)
    {
        sound->setBuffer(*buffer);
        sound->setLoop(false);
        sound->setVolume(volume_sfx);
        sound->play();
        sfx_temp.add(sound);      // if success ad to sfx_temp
    }
    else
    {
        unused_sound.add(sound);
        cout << "error retriving sound: " << name << endl;
        return;
    }
}

void AudioManager::playMusic(string name, bool destroy_old)
{
    // check number of sounds
    int total_sounds = sfx_temp.getSize() + music_temp.getSize();

    // if max decide to destroy old sound or not
    if (total_sounds >= max_sounds && destroy_old)
    {
        if (music_temp.getSize() == 0) return; // no sounds to recycle so cannot play the new sound

        // destroy the old sound and add it to the recycled
        sf::Music* recycled_music = music_temp.getRoot()->data;
        recycled_music->stop();
        music_temp.remove(music_temp.getRoot());
        unused_music.add(recycled_music);
    }
    else if (total_sounds >= max_sounds)
    {
        return; // not going to play the sound
    }

    // if not max create new music or recycle expired
    sf::Music* music = nullptr;
    if (unused_music.getSize() > 0)
    {
        music = unused_music.getLast()->data;
        unused_music.remove(unused_music.getLast());
    }
    else
    {
        music = new sf::Music();
    }

    string audio_file = gdata.assets->getMusic(name);
    if (music->openFromFile(audio_file))
    {
        music->setLoop(false);
        music->setVolume(volume_music);
        music->play();
        music_temp.add(music);
    }
    else
    {
        unused_music.add(music);
        cout << "error loading music file: " << audio_file << endl;
        return;
    }
}

sf::Sound* AudioManager::addSound(string name)
{

}

sf::Music* AudioManager::addMusic(string name)
{

}

void AudioManager::freeResources()
{

}

