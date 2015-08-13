#include "AssetManager.h"

AssetManager::AssetManager()
{
    //ctor
}

AssetManager::~AssetManager()
{
    //dtor
}

bool AssetManager::loadAssetList(std::string path)
{
    bool result = false;

    try
    {
        XMLDocument doc;
        XMLError error = doc.LoadFile(path.c_str());

        if (error != XML_NO_ERROR)
        {
            gz::print_w("Error loading assets.xml error#" + XML_NO_ERROR);
            return false;
        }

        XMLElement* root = doc.RootElement();

        if (!root)
        {
            gz::print_w("Error getting root element");  // no root element
            return false;
        }


        loadAssets(root);
        result = true;

    }
    catch ( std::exception& ex )
    {
        gz::print_w("Exception Thrown:" + gz::toString(ex.what()) );
    }

    return result;
}

void AssetManager::loadAssets(XMLElement* root)
{
    XMLElement* element = root->FirstChildElement("asset");
    while (element)
    {
        std::string attribute_type = element->Attribute("type");
        std::string attribute_path = element->Attribute("path");

        if (attribute_type == "image")      addTexture(attribute_path);
        else if (attribute_type == "sound") addSound(attribute_path);
        else if (attribute_type == "music") addMusic(attribute_path);
        else if (attribute_type == "font")  addFont(attribute_path);

        element = element->NextSiblingElement("asset");
    }
}

void AssetManager::addFont(std::string path)
{
    std::string fileName = gz::getFileName(path);
    std::string extension = gz::getFileExtension(path);

    sdlFont* font = new sdlFont();

    bool load_success = font->loadFromFile(path);
    if (load_success)
        m_fonts.insert( pairFont(fileName,font));
    else
        gz::print_w("There were errors loading the font: " + path);
}


void AssetManager::addMusic(std::string path)
{
	std::string fileName = gz::getFileName(path);

	if (m_music.find(fileName) == m_music.end())
	{
		Mix_Music* snd = Mix_LoadMUS(path.c_str());
		if (snd != nullptr)
		{
			m_music.insert(pairMusic(fileName, snd));
		}
		else
		{
			gz::print_w("Failed to load track: " + path);
		}
	}
	else
	{
		gz::print_w("file with name already exists. track was not loaded");
	}
}


void AssetManager::addSound(std::string path)
{
    std::string fileName = gz::getFileName(path);

    if (m_sounds.find(fileName) == m_sounds.end())
    {
		Mix_Chunk* snd = Mix_LoadWAV(path.c_str());
        if (snd != nullptr)
        {
            m_sounds.insert( pairSound(fileName, snd) );
        }
        else
        {
            gz::print_w("Failed to load sound: " + path);
        }
    }
    else
    {
        gz::print_w("file with name already exists. sound was not loaded");
    }
}

void AssetManager::addTexture(std::string path)
{
    std::string fileName = gz::getFileName(path);
	cout << path << endl;
    if ( m_textures.find(fileName) == m_textures.end() )
    {

        SDL_Texture* texture = IMG_LoadTexture(renderer,path.c_str());
		if (texture != nullptr)
		{
			cout << "adding texture " << fileName << endl;
			m_textures.insert(pairTexture(fileName, texture));
		}
		else
		{
			gz::print_w("Failed to load image: " + path);
		}
    }
    else
    {
        gz::print_w("file with name already exists. Image was not loaded");
    }
}

void AssetManager::freeResources()
{
    for (map_textures::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
    {
        delete (*it).second;
    }
    m_textures.clear();

    for (map_sounds::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it)
    {
		Mix_FreeChunk((*it).second);
        (*it).second = nullptr;
    }
    m_sounds.clear();

	for (map_music::iterator it = m_music.begin(); it != m_music.end(); ++it)
	{
		Mix_FreeMusic((*it).second);
		(*it).second = nullptr;
	}
	m_music.clear();

    for (map_fonts::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
    {
        (*it).second->free();
        delete (*it).second;
    }
    m_fonts.clear();
}

SDL_Texture* AssetManager::getTexture(std::string name)
{
    SDL_Texture* result = nullptr;
    if ( m_textures.find(name) != m_textures.end() )
        result = m_textures.at(name);
    return result;
}

Mix_Chunk* AssetManager::getSound(std::string name)
{
	Mix_Chunk* result = nullptr;
    if ( m_sounds.find(name) != m_sounds.end() )
        result = m_sounds.at(name);
    return result;
}

Mix_Music* AssetManager::getMusic(std::string name)
{
    Mix_Music* result = nullptr;
    if ( m_music.find(name) != m_music.end() )
        result = m_music.at(name);
    return result;
}

sdlFont* AssetManager::getFont(std::string name)
{
   sdlFont* result = nullptr;
    if ( m_fonts.find(name) != m_fonts.end() )
        result = m_fonts.at(name);
    return result;
}


