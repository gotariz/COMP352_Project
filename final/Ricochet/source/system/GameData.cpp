#include "GameData.h"

GameData gdata;

GameData::GameData()
{
    keys.reserve( sf::Keyboard::KeyCount + 7 );
    for (unsigned i = 0; i < sf::Keyboard::KeyCount + 7; ++i)
    {
        keys.push_back( KeyboardKey(sf::Keyboard::Unknown,"unknown") );
    }

    //ctor
    keys.at(sf::Keyboard::A) = KeyboardKey(sf::Keyboard::A,"A");
    keys.at(sf::Keyboard::B) = KeyboardKey(sf::Keyboard::B,"B");
    keys.at(sf::Keyboard::C) = KeyboardKey(sf::Keyboard::C,"C");
    keys.at(sf::Keyboard::D) = KeyboardKey(sf::Keyboard::D,"D");
    keys.at(sf::Keyboard::E) = KeyboardKey(sf::Keyboard::E,"E");
    keys.at(sf::Keyboard::F) = KeyboardKey(sf::Keyboard::F,"F");
    keys.at(sf::Keyboard::G) = KeyboardKey(sf::Keyboard::G,"G");
    keys.at(sf::Keyboard::H) = KeyboardKey(sf::Keyboard::H,"H");
    keys.at(sf::Keyboard::I) = KeyboardKey(sf::Keyboard::I,"I");
    keys.at(sf::Keyboard::J) = KeyboardKey(sf::Keyboard::J,"J");
    keys.at(sf::Keyboard::K) = KeyboardKey(sf::Keyboard::K,"K");
    keys.at(sf::Keyboard::L) = KeyboardKey(sf::Keyboard::L,"L");
    keys.at(sf::Keyboard::M) = KeyboardKey(sf::Keyboard::M,"M");
    keys.at(sf::Keyboard::N) = KeyboardKey(sf::Keyboard::N,"N");
    keys.at(sf::Keyboard::O) = KeyboardKey(sf::Keyboard::O,"O");
    keys.at(sf::Keyboard::P) = KeyboardKey(sf::Keyboard::P,"P");
    keys.at(sf::Keyboard::Q) = KeyboardKey(sf::Keyboard::Q,"Q");
    keys.at(sf::Keyboard::R) = KeyboardKey(sf::Keyboard::R,"R");
    keys.at(sf::Keyboard::S) = KeyboardKey(sf::Keyboard::S,"S");
    keys.at(sf::Keyboard::T) = KeyboardKey(sf::Keyboard::T,"T");
    keys.at(sf::Keyboard::U) = KeyboardKey(sf::Keyboard::U,"U");
    keys.at(sf::Keyboard::V) = KeyboardKey(sf::Keyboard::V,"V");
    keys.at(sf::Keyboard::W) = KeyboardKey(sf::Keyboard::W,"W");
    keys.at(sf::Keyboard::X) = KeyboardKey(sf::Keyboard::X,"X");
    keys.at(sf::Keyboard::Y) = KeyboardKey(sf::Keyboard::Y,"Y");
    keys.at(sf::Keyboard::Z) = KeyboardKey(sf::Keyboard::Z,"Z");

    keys.at(sf::Keyboard::Num0) = KeyboardKey(sf::Keyboard::Num0,"0");
    keys.at(sf::Keyboard::Num1) = KeyboardKey(sf::Keyboard::Num1,"1");
    keys.at(sf::Keyboard::Num2) = KeyboardKey(sf::Keyboard::Num2,"2");
    keys.at(sf::Keyboard::Num3) = KeyboardKey(sf::Keyboard::Num3,"3");
    keys.at(sf::Keyboard::Num4) = KeyboardKey(sf::Keyboard::Num4,"4");
    keys.at(sf::Keyboard::Num5) = KeyboardKey(sf::Keyboard::Num5,"5");
    keys.at(sf::Keyboard::Num6) = KeyboardKey(sf::Keyboard::Num6,"6");
    keys.at(sf::Keyboard::Num7) = KeyboardKey(sf::Keyboard::Num7,"7");
    keys.at(sf::Keyboard::Num8) = KeyboardKey(sf::Keyboard::Num8,"8");
    keys.at(sf::Keyboard::Num9) = KeyboardKey(sf::Keyboard::Num9,"9");

    keys.at(sf::Keyboard::Escape)    = KeyboardKey(sf::Keyboard::Escape,"Escape");
    keys.at(sf::Keyboard::LControl)  = KeyboardKey(sf::Keyboard::LControl,"Left Ctrl");
    keys.at(sf::Keyboard::LShift)    = KeyboardKey(sf::Keyboard::LShift,"Left Shift");
    keys.at(sf::Keyboard::LAlt)      = KeyboardKey(sf::Keyboard::LAlt,"Left Alt");
    keys.at(sf::Keyboard::LSystem)   = KeyboardKey(sf::Keyboard::LSystem,"Left System");
    keys.at(sf::Keyboard::RControl)  = KeyboardKey(sf::Keyboard::RControl,"Right Ctrl");
    keys.at(sf::Keyboard::RShift)    = KeyboardKey(sf::Keyboard::RShift,"Right Shift");
    keys.at(sf::Keyboard::RAlt)      = KeyboardKey(sf::Keyboard::RAlt,"Right Alt");
    keys.at(sf::Keyboard::RSystem)   = KeyboardKey(sf::Keyboard::RSystem,"Right System");
    keys.at(sf::Keyboard::Menu)      = KeyboardKey(sf::Keyboard::Menu,"Menu");

    keys.at(sf::Keyboard::LBracket)  = KeyboardKey(sf::Keyboard::LBracket,"[");
    keys.at(sf::Keyboard::RBracket)  = KeyboardKey(sf::Keyboard::RBracket,"]");
    keys.at(sf::Keyboard::SemiColon) = KeyboardKey(sf::Keyboard::Menu,";");
    keys.at(sf::Keyboard::Comma)     = KeyboardKey(sf::Keyboard::Menu,",");
    keys.at(sf::Keyboard::Period)    = KeyboardKey(sf::Keyboard::Menu,".");
    keys.at(sf::Keyboard::Quote)     = KeyboardKey(sf::Keyboard::Menu,"'");
    keys.at(sf::Keyboard::Slash)     = KeyboardKey(sf::Keyboard::Menu,"/");
    keys.at(sf::Keyboard::BackSlash) = KeyboardKey(sf::Keyboard::Menu,"\\");

    keys.at(sf::Keyboard::Tilde)     = KeyboardKey(sf::Keyboard::Tilde,"~");
    keys.at(sf::Keyboard::Equal)     = KeyboardKey(sf::Keyboard::Equal,"=");
    keys.at(sf::Keyboard::Dash)      = KeyboardKey(sf::Keyboard::Dash,"-");
    keys.at(sf::Keyboard::Space)     = KeyboardKey(sf::Keyboard::Space,"Space");
    keys.at(sf::Keyboard::Return)    = KeyboardKey(sf::Keyboard::Return,"Return");
    keys.at(sf::Keyboard::BackSpace) = KeyboardKey(sf::Keyboard::BackSpace,"Backspace");
    keys.at(sf::Keyboard::Tab)       = KeyboardKey(sf::Keyboard::Tab,"Tab");
    keys.at(sf::Keyboard::PageUp)    = KeyboardKey(sf::Keyboard::PageUp,"Page Up");
    keys.at(sf::Keyboard::PageDown)  = KeyboardKey(sf::Keyboard::PageDown,"Page Down");
    keys.at(sf::Keyboard::End)       = KeyboardKey(sf::Keyboard::End,"End");
    keys.at(sf::Keyboard::Home)      = KeyboardKey(sf::Keyboard::Home,"Home");
    keys.at(sf::Keyboard::Insert)    = KeyboardKey(sf::Keyboard::Insert,"Insert");
    keys.at(sf::Keyboard::Delete)    = KeyboardKey(sf::Keyboard::Delete,"Delete");
    keys.at(sf::Keyboard::Add)       = KeyboardKey(sf::Keyboard::Add,"Numpad +");
    keys.at(sf::Keyboard::Subtract)  = KeyboardKey(sf::Keyboard::Subtract,"Numpad -");
    keys.at(sf::Keyboard::Multiply)  = KeyboardKey(sf::Keyboard::Multiply,"Numpad *");
    keys.at(sf::Keyboard::Divide)    = KeyboardKey(sf::Keyboard::Divide,"Numpad /");
    keys.at(sf::Keyboard::Left)      = KeyboardKey(sf::Keyboard::Left,"Left Arrow");
    keys.at(sf::Keyboard::Right)     = KeyboardKey(sf::Keyboard::Right,"Right Arrow");
    keys.at(sf::Keyboard::Up)        = KeyboardKey(sf::Keyboard::Up,"Up Arrow");
    keys.at(sf::Keyboard::Down)      = KeyboardKey(sf::Keyboard::Down,"Down Arrow");

    keys.at(sf::Keyboard::Numpad0) = KeyboardKey(sf::Keyboard::Numpad0,"Numpad 0");
    keys.at(sf::Keyboard::Numpad1) = KeyboardKey(sf::Keyboard::Numpad1,"Numpad 1");
    keys.at(sf::Keyboard::Numpad2) = KeyboardKey(sf::Keyboard::Numpad2,"Numpad 2");
    keys.at(sf::Keyboard::Numpad3) = KeyboardKey(sf::Keyboard::Numpad3,"Numpad 3");
    keys.at(sf::Keyboard::Numpad4) = KeyboardKey(sf::Keyboard::Numpad4,"Numpad 4");
    keys.at(sf::Keyboard::Numpad5) = KeyboardKey(sf::Keyboard::Numpad5,"Numpad 5");
    keys.at(sf::Keyboard::Numpad6) = KeyboardKey(sf::Keyboard::Numpad6,"Numpad 6");
    keys.at(sf::Keyboard::Numpad7) = KeyboardKey(sf::Keyboard::Numpad7,"Numpad 7");
    keys.at(sf::Keyboard::Numpad8) = KeyboardKey(sf::Keyboard::Numpad8,"Numpad 8");
    keys.at(sf::Keyboard::Numpad9) = KeyboardKey(sf::Keyboard::Numpad9,"Numpad 9");

    keys.at(sf::Keyboard::F1)    = KeyboardKey(sf::Keyboard::F1,"F1");
    keys.at(sf::Keyboard::F2)    = KeyboardKey(sf::Keyboard::F2,"F2");
    keys.at(sf::Keyboard::F3)    = KeyboardKey(sf::Keyboard::F3,"F3");
    keys.at(sf::Keyboard::F4)    = KeyboardKey(sf::Keyboard::F4,"F4");
    keys.at(sf::Keyboard::F5)    = KeyboardKey(sf::Keyboard::F5,"F5");
    keys.at(sf::Keyboard::F6)    = KeyboardKey(sf::Keyboard::F6,"F6");
    keys.at(sf::Keyboard::F7)    = KeyboardKey(sf::Keyboard::F7,"F7");
    keys.at(sf::Keyboard::F8)    = KeyboardKey(sf::Keyboard::F8,"F8");
    keys.at(sf::Keyboard::F9)    = KeyboardKey(sf::Keyboard::F9,"F9");
    keys.at(sf::Keyboard::F10)   = KeyboardKey(sf::Keyboard::F10,"F10");
    keys.at(sf::Keyboard::F11)   = KeyboardKey(sf::Keyboard::F11,"F11");
    keys.at(sf::Keyboard::F12)   = KeyboardKey(sf::Keyboard::F12,"F12");
    keys.at(sf::Keyboard::F13)   = KeyboardKey(sf::Keyboard::F13,"F13/Print Screen");
    keys.at(sf::Keyboard::F14)   = KeyboardKey(sf::Keyboard::F14,"F14/Screen Lock");
    keys.at(sf::Keyboard::F15)   = KeyboardKey(sf::Keyboard::F15,"F15/Pause");

    keys.at(KEY_MOUSE_LEFT)               = KeyboardKey(KEY_MOUSE_LEFT,"mouse left");
    keys.at(KEY_MOUSE_RIGHT)              = KeyboardKey(KEY_MOUSE_RIGHT,"mouse right");
    keys.at(KEY_MOUSE_MIDDLE)             = KeyboardKey(KEY_MOUSE_MIDDLE,"mouse middle");
    keys.at(KEY_MOUSE_BUTTON_4)           = KeyboardKey(KEY_MOUSE_BUTTON_4,"mouse button 4");
    keys.at(KEY_MOUSE_BUTTON_5)           = KeyboardKey(KEY_MOUSE_BUTTON_5,"mouse button 5");
    keys.at(KEY_MOUSE_SCROLL_UP)          = KeyboardKey(KEY_MOUSE_SCROLL_UP,"mouse scroll up");
    keys.at(KEY_MOUSE_SCROLL_DOWN)        = KeyboardKey(KEY_MOUSE_SCROLL_DOWN,"mouse scroll down");
}

void GameData::updateKeys()
{
    for (unsigned i = 0; i < keys.size() - 7; ++i)
    {
        keys.at(i).updateKey( sf::Keyboard::isKeyPressed(keys.at(i).m_key) );
    }

    keys.at(KEY_MOUSE_LEFT).updateKey( sf::Mouse::isButtonPressed(sf::Mouse::Left) );
    keys.at(KEY_MOUSE_RIGHT).updateKey( sf::Mouse::isButtonPressed(sf::Mouse::Right) );
    keys.at(KEY_MOUSE_MIDDLE).updateKey( sf::Mouse::isButtonPressed(sf::Mouse::Middle) );
    keys.at(KEY_MOUSE_BUTTON_4).updateKey( sf::Mouse::isButtonPressed(sf::Mouse::XButton1) );
    keys.at(KEY_MOUSE_BUTTON_5).updateKey( sf::Mouse::isButtonPressed(sf::Mouse::XButton2) );
}

/*
GameData::~GameData()
{
    //dtor
}

void GameData::setDeltaTime(float dt)
{
//    if (dt > MAX_TIME_STEP)
//    {
//        deltaTime = MAX_TIME_STEP;
//        deltaTimeExcess = dt - MAX_TIME_STEP;
//    }
//    else
    {
        m_deltaTime = dt;
        m_deltaTimeExcess = 0;
    }
}

int GameData::getScreenWidth()
{
    return m_window->getSize().x;
}

int GameData::getScreenHeight()
{
    return m_window->getSize().y;
}

int GameData::getHalfScreenWidth()
{
    return m_window->getSize().x / 2;
}

int GameData::getHalfScreenHeight()
{
    return m_window->getSize().y / 2;
}

*/
Vector2 GameData::toPixels(float x, float y)
{

	int pixel_x = window->getSize().x / 2 + (x * (WORLD_SCALE * zoom));
	int pixel_y = window->getSize().y / 2 - (y * (WORLD_SCALE * zoom));

    return Vector2(pixel_x,pixel_y);
}

Vector2 GameData::toPixels(Vector2 p)
{

	int pixel_x = window->getSize().x / 2 + (p.x * (WORLD_SCALE * zoom));
	int pixel_y = window->getSize().y / 2 - (p.y * (WORLD_SCALE * zoom));

    return Vector2(pixel_x,pixel_y);
}

Vector2 GameData::toPixels(b2Vec2 p)
{

	int pixel_x = window->getSize().x / 2 + (p.x * (WORLD_SCALE * zoom));
	int pixel_y = window->getSize().y / 2 - (p.y * (WORLD_SCALE * zoom));

    return Vector2(pixel_x,pixel_y);
}

Vector2 GameData::toScreenPixels(float x, float y)
{
    int pixel_x = window->getSize().x / 2 + (x * (WORLD_SCALE * zoom));
	int pixel_y = window->getSize().y / 2 - (y * (WORLD_SCALE * zoom));

	pixel_x -= camera->x * (WORLD_SCALE * gdata.zoom);
	pixel_y -= -camera->y * (WORLD_SCALE * gdata.zoom);

    return Vector2(pixel_x,pixel_y);
}

Vector2 GameData::toScreenPixels(Vector2 p)
{
    int pixel_x = window->getSize().x / 2 + (p.x * (WORLD_SCALE * zoom));
	int pixel_y = window->getSize().y / 2 - (p.y * (WORLD_SCALE * zoom));

	pixel_x -= camera->x * (WORLD_SCALE * gdata.zoom);
	pixel_y -= -camera->y * (WORLD_SCALE * gdata.zoom);

    return Vector2(pixel_x,pixel_y);
}

Vector2 GameData::toScreenPixels(b2Vec2 p)
{
    int pixel_x = window->getSize().x / 2 + (p.x * (WORLD_SCALE * zoom));
	int pixel_y = window->getSize().y / 2 - (p.y * (WORLD_SCALE * zoom));

	pixel_x -= camera->x * (WORLD_SCALE * gdata.zoom);
	pixel_y -= -camera->y * (WORLD_SCALE * gdata.zoom);

    return Vector2(pixel_x,pixel_y);
}



