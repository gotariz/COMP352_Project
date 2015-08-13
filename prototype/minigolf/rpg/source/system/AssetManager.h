#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <sys/stat.h>

#include "general.h"
#include "video/sdlFont.h"

using namespace tinyxml2;

class AssetManager
{
    public:
        AssetManager();
        virtual ~AssetManager();

        bool loadAssetList(std::string path);
        void freeResources();

        SDL_Texture*        getTexture(std::string name);
        Mix_Chunk*			getSound(std::string name);
        Mix_Music*			getMusic(std::string name);
        sdlFont*            getFont(std::string name);

		SDL_Renderer* renderer = nullptr;

    private:
        map<string,SDL_Texture*>		m_textures;
        map<string,Mix_Chunk*>			m_sounds;
        map<string,Mix_Music*>			m_music;
        std::map<std::string,sdlFont*>  m_fonts;

        // typedef
        typedef std::map<std::string,SDL_Texture*>      map_textures;
        typedef std::map<std::string,Mix_Chunk*>		map_sounds;
        typedef std::map<std::string,Mix_Music*>		map_music;
        typedef std::map<std::string,sdlFont*>          map_fonts;

        typedef std::pair<std::string,SDL_Texture*>     pairTexture;
        typedef std::pair<std::string,Mix_Chunk*>		pairSound;
        typedef std::pair<std::string,Mix_Music*>		pairMusic;
        typedef std::pair<std::string,sdlFont*>         pairFont;

        // conveniance function
        void loadAssets(XMLElement* root);
        void addTexture(std::string path);
        void addSound(std::string path);
        void addMusic(std::string path);
        void addFont(std::string path);
};

#endif // ASSETMANAGER_H
