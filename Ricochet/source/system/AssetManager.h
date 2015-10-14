#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "general.h"
#include "video/sfFont.h"

using namespace tinyxml2;

class AssetManager
{
    public:
        AssetManager();
        virtual ~AssetManager();

        bool loadAssetList(std::string path);
        void freeResources();

        sf::Texture*        getTexture(std::string name);
        sf::SoundBuffer*    getSound(std::string name);
        std::string         getMusic(std::string name);
        sfFont*             getFont(std::string name);

        sf::SoundBuffer* snd = nullptr;

    private:
        std::map<std::string,sf::Texture*>      m_textures;
        std::map<std::string,sf::SoundBuffer*>  m_sounds;
        std::map<std::string,std::string>       m_music;
        std::map<std::string,sfFont*>           m_fonts;

        // typedef
        typedef std::map<std::string,sf::Texture*>      map_textures;
        typedef std::map<std::string,sf::SoundBuffer*>  map_sounds;
        typedef std::map<std::string,std::string>       map_music;
        typedef std::map<std::string,sfFont*>           map_fonts;

        typedef std::pair<std::string,sf::Texture*>     pairTexture;
        typedef std::pair<std::string,sf::SoundBuffer*> pairSound;
        typedef std::pair<std::string,std::string>      pairMusic;
        typedef std::pair<std::string,sfFont*>          pairFont;

        // conveniance function
        void loadAssets(XMLElement* root);
        void addTexture(std::string path);
        void addSound(std::string path);
        void addMusic(std::string path);
        void addFont(std::string path);
};

#endif // ASSETMANAGER_H
