#include "AudioManager.h"

AudioManager::AudioManager()
{
    //ctor
}

AudioManager::~AudioManager()
{
    //dtor
}

void AudioManager::setVolumeSFX(float volume)
{
    Node<SoundHandle*>* node = sfx_temp.getRoot();
    while (node)
    {
        node->data->volume(volume);
        node = node->next;
    }

    node = sfx_perm.getRoot();
    while (node)
    {
        node->data->volume(volume);
        node = node->next;
    }
}

void AudioManager::setVolumeMusic(float volume)
{
    Node<MusicHandle*>* node = music_temp.getRoot();
    while (node)
    {
        node->data->volume(volume);
        node = node->next;
    }

    node = music_perm.getRoot();
    while (node)
    {
        node->data->volume(volume);
        node = node->next;
    }
}


void AudioManager::update()
{

    Node<SoundHandle*>* soundNode = sfx_temp.getRoot();
    Node<SoundHandle*>* soundNext = nullptr;
    while (soundNode)
    {
        soundNext = soundNode->next;
        if (soundNode->data->isFinished())
        {
            soundNode->data->node = nullptr;
            unused_sound.add(soundNode->data);
            sfx_temp.remove(soundNode);
        }
        soundNode = soundNext;
    }

    Node<MusicHandle*>* musicNode = music_temp.getRoot();
    Node<MusicHandle*>* musicNext = nullptr;
    while (musicNode)
    {
        musicNext = musicNode->next;
        if (musicNode->data->isFinished())
        {
            musicNode->data->node = nullptr;
            unused_music.add(musicNode->data);
            music_temp.remove(musicNode);
        }
        musicNode = musicNext;
    }
}

void AudioManager::removeTempSound()
{
    if (sfx_temp.getSize() == 0) return; // no sounds to recycle so cannot play the new sound

    SoundHandle* recycled_sound = sfx_temp.getRoot()->data;
    recycled_sound->stop();
    recycled_sound->node = nullptr;

    sfx_temp.remove(sfx_temp.getRoot());
    unused_sound.add(recycled_sound);
}

void AudioManager::removeTempMusic()
{
    if (music_temp.getSize() == 0) return; // no sounds to recycle so cannot play the new sound

    // destroy the old sound and add it to the recycled
    MusicHandle* recycled_music = music_temp.getRoot()->data;
    recycled_music->stop();
    recycled_music->node = nullptr;

    music_temp.remove(music_temp.getRoot());
    unused_music.add(recycled_music);
}


void AudioManager::playSound(string name, bool destroy_old)
{
    // check number of sounds
    int total_sounds = sfx_temp.getSize() + music_temp.getSize();

    // if max decide to destroy old sound or not
    if (total_sounds >= max_sounds && destroy_old)  removeTempSound();
    else if (total_sounds >= max_sounds)            return;


    // if not max create new sound or recycle expired
    SoundHandle* handle = nullptr;
    if (unused_sound.getSize() > 0)
    {
        handle = unused_sound.getLast()->data;
        unused_sound.remove(unused_sound.getLast());
    }
    else
    {
        cout << "creating sound" << endl;
        handle = new SoundHandle;
    }

    // set sound properties
    sf::SoundBuffer* buffer = gdata.assets->getSound(name);

    if (buffer)
    {
        handle->sound.setBuffer(*buffer);
        handle->loop(false);
        handle->volume(volume_sfx);
        handle->play();
        Node<SoundHandle*>* node = sfx_temp.add(handle);      // if success ad to sfx_temp
        handle->node = node;
    }
    else
    {
        unused_sound.add(handle);
        cout << "error retriving sound: " << name << endl;
        return;
    }
}

void AudioManager::playMusic(string name, bool destroy_old)
{
    // check number of sounds
    int total_sounds = sfx_temp.getSize() + music_temp.getSize();

    // if max decide to destroy old sound or not
    if (total_sounds >= max_sounds && destroy_old)  removeTempMusic();
    else if (total_sounds >= max_sounds)            return; // not going to play the sound

    // if not max create new music or recycle expired
    MusicHandle* handle = nullptr;
    if (unused_music.getSize() > 0)
    {
        handle = unused_music.getLast()->data;
        unused_music.remove(unused_music.getLast());
    }
    else
    {
        handle = new MusicHandle;
    }

    string audio_file = gdata.assets->getMusic(name);
    if (handle->music.openFromFile(audio_file))
    {
        handle->loop(false);
        handle->volume(volume_music);
        handle->play();
        Node<MusicHandle*>* node = music_temp.add(handle);
        handle->node = node;
    }
    else
    {
        unused_music.add(handle);
        cout << "error loading music file: " << audio_file << endl;
        return;
    }
}

SoundHandle* AudioManager::addSound(string name, bool destroy_old)
{
    // check number of sounds
    int total_sounds = sfx_temp.getSize() + music_temp.getSize();

    // if max decide to destroy old sound or not
    if (total_sounds >= max_sounds && destroy_old)  removeTempSound();
    else if (total_sounds >= max_sounds)            return nullptr; // not going to play the sound

    // if not max create new sound or recycle expired
    SoundHandle* handle = nullptr;
    if (unused_sound.getSize() > 0)
    {
        handle = unused_sound.getLast()->data;
        unused_sound.remove(unused_sound.getLast());
    }
    else
    {
        cout << "creating sound" << endl;
        handle = new SoundHandle;
    }

    // set sound properties
    sf::SoundBuffer* buffer = gdata.assets->getSound(name);

    if (buffer)
    {
        handle->sound.setBuffer(*buffer);
        handle->loop(false);
        handle->volume(volume_sfx);
        handle->play();
        Node<SoundHandle*>* node = sfx_temp.add(handle);      // if success ad to sfx_temp
        handle->node = node;
    }
    else
    {
        unused_sound.add(handle);
        cout << "error retriving sound: " << name << endl;
        return nullptr;
    }
}

MusicHandle* AudioManager::addMusic(string name, bool destroy_old)
{
    // check number of sounds
    int total_sounds = sfx_temp.getSize() + music_temp.getSize();

    // if max decide to destroy old sound or not
    if (total_sounds >= max_sounds && destroy_old)  removeTempMusic();
    else if (total_sounds >= max_sounds)            return nullptr; // not going to play the sound

    // if not max create new music or recycle expired
    MusicHandle* handle = nullptr;
    if (unused_music.getSize() > 0)
    {
        handle = unused_music.getLast()->data;
        unused_music.remove(unused_music.getLast());
    }
    else
    {
        handle = new MusicHandle;
    }

    string audio_file = gdata.assets->getMusic(name);
    if (handle->music.openFromFile(audio_file))
    {
        handle->loop(false);
        handle->volume(volume_music);
        handle->play();
        Node<MusicHandle*>* node = music_perm.add(handle);
        handle->node = node;

        return handle;
    }
    else
    {
        unused_music.add(handle);
        cout << "error loading music file: " << audio_file << endl;
        return nullptr;
    }

}

void AudioManager::freeResources()
{
    Node<SoundHandle*>* a = unused_sound.getRoot();
    while (a)
    {
        a->data->stop();
        delete a->data;
        a = a->next;
    }
    unused_sound.clear();

    Node<MusicHandle*>* b = unused_music.getRoot();
    while (b)
    {
        b->data->stop();
        delete b->data;
        b = b->next;
    }
    unused_music.clear();

    Node<SoundHandle*>* c = sfx_temp.getRoot();
    while (c)
    {
        c->data->stop();
        delete c->data;
        c = c->next;
    }
    sfx_temp.clear();

    Node<SoundHandle*>* d = sfx_perm.getRoot();
    while (d)
    {
        d->data->stop();
        delete d->data;
        d = d->next;
    }
    sfx_perm.clear();

    Node<MusicHandle*>* e = music_temp.getRoot();
    while (e)
    {
        e->data->stop();
        delete e->data;
        e = e->next;
    }
    music_temp.clear();

    Node<MusicHandle*>* f = music_perm.getRoot();
    while (f)
    {
        f->data->stop();
        delete f->data;
        f = f->next;
    }
    music_perm.clear();
}

