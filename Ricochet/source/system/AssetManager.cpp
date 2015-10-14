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
    //std::string extension = gz::getFileExtension(path);

    sfFont* font = new sfFont();

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
        m_music.insert( pairMusic(fileName, path) );
    else
        gz::print_w("file with name already exists. sound was not loaded");
}


void AssetManager::addSound(std::string path)
{
    std::string fileName = gz::getFileName(path);

    if (m_sounds.find(fileName) == m_sounds.end())
    {
        sf::SoundBuffer* buffer = new sf::SoundBuffer;
        if (buffer->loadFromFile(path))
        {
            m_sounds.insert( pairSound(fileName, buffer) );
        }
        else
        {
            delete buffer;
            gz::print_w("Failed to load sound buffer: " + path);
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

    if ( m_textures.find(fileName) == m_textures.end() )
    {
        sf::Texture* texture = new sf::Texture;

        if (texture->loadFromFile(path))
        {
            texture->setSmooth(true);
            m_textures.insert( pairTexture(fileName, texture) );
        }
        else
        {
            delete texture;
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
        delete (*it).second;
    }
    m_sounds.clear();

    for (map_fonts::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
    {
        (*it).second->free();
        delete (*it).second;
    }
    m_fonts.clear();
}

sf::Texture* AssetManager::getTexture(std::string name)
{
    sf::Texture* result = nullptr;
    if ( m_textures.find(name) != m_textures.end() )
        result = m_textures.at(name);
    else
        cout << "could not find texture " << name << " returning nullptr" << endl;

    return result;
}

sf::SoundBuffer* AssetManager::getSound(std::string name)
{
    sf::SoundBuffer* result = nullptr;
    if ( m_sounds.find(name) != m_sounds.end() )
        result = m_sounds.at(name);
    else
        cout << "could not find sound " << name << " returning nullptr" << endl;

    return result;
}

std::string AssetManager::getMusic(std::string name)
{
    std::string result = "";
    if ( m_music.find(name) != m_music.end() )
        result = m_music.at(name);
    else
        cout << "could not find music " << name << " returning \"\"" << endl;

    return result;
}

sfFont* AssetManager::getFont(std::string name)
{
   sfFont* result = nullptr;
    if ( m_fonts.find(name) != m_fonts.end() )
        result = m_fonts.at(name);
    else
        cout << "could not find sfFont " << name << " returning nullptr" << endl;
    return result;
}


