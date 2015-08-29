#include "Settings.h"
Settings::Settings()
{

}

Settings::~Settings()
{

}

bool Settings::getVsync() const
{
    return m_vsync;
}

bool Settings::getFullscreen() const
{
    return m_fullscreen;
}

unsigned Settings::getScreenWidth() const
{
    return m_resolution.w;
}

unsigned Settings::getScreenHeight() const
{
    return m_resolution.h;
}

unsigned Settings::getFpsLimit() const
{
    return m_fpsLimit;
}

void Settings::setVsync(bool vsync)
{
    m_vsync = vsync;
}

void Settings::setFullscreen(bool fullscreen)
{
    m_fullscreen = fullscreen;
}

void Settings::setScreenWidth(int width)
{
    m_resolution.w = width;
}

void Settings::setScreenHeight(int height)
{
    m_resolution.h = height;
}

void Settings::setFpsLimit(int fps_limit)
{
    m_fpsLimit = fps_limit;
}


void Settings::saveSettings()
{
    ofstream s ("data/config.ini");

    if (s.is_open())
    {
        s << "fps=" << m_fpsLimit << endl;;
        s << "fullscreen=" << (m_fullscreen ? "true" : "false") << endl;;
        s << "width=" << m_resolution.w << endl;;
        s << "height=" << m_resolution.h << endl;;
        s << "vsync=" << m_vsync << endl;;
        s.close();
    }
    else
    {
        cout << "Unable to open config.ini";
    }
}

void Settings::readSettings()
{
    std::string line;
    std::ifstream file;
    file.open(SETTINGS_FILENAME);

    if (file.is_open())
    {
        while(getline(file,line))
        {
            std::pair<std::string,std::string> p = gz::getValuePair(line);
            std::string name = p.first;
            std::string value = p.second;

            if (name == "fpsLimit")
            {
                m_fpsLimit = gz::toInt(value.c_str(),SETTINGS_DEFAULT_FPSLIMIT);
            }
            else if (name == "fullscreen")
            {
                m_fullscreen = gz::toBool(value.c_str());
            }
            else if (name == "vsync")
            {
                m_vsync = gz::toBool(value.c_str());
            }
            else if (name == "width")
            {
                m_resolution.w = gz::toInt(value.c_str(),SETTINGS_DEFAULT_WIDTH);
            }
            else if (name == "height")
            {
                m_resolution.h = gz::toInt(value.c_str(),SETTINGS_DEFAULT_HEIGHT);
            }
        }

        gz::print_value("fpsLimit:  ",m_fpsLimit);
        gz::print_value("fullscreen:",m_fullscreen);
        gz::print_value("vsync:     ",m_vsync);
        gz::print_value("width:     ",m_resolution.w);
        gz::print_value("height:    ",m_resolution.h);

    }
    else
    {
        gz::log_error("Unable to open file: " + SETTINGS_FILENAME );
    }
    file.close();
}

