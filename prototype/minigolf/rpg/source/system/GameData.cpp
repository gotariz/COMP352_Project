#include "GameData.h"

GameData gdata;

GameData::GameData()
{
    keys.reserve( 282 );
    for (unsigned i = 0; i < 300; ++i)
    {
        keys.push_back( NULL );
    }

    //Alphabet
	keys[SDL_SCANCODE_A] = new KeyboardKey(SDL_SCANCODE_A, "A");
	keys[SDL_SCANCODE_B] = new KeyboardKey(SDL_SCANCODE_B, "B");
	keys[SDL_SCANCODE_C] = new KeyboardKey(SDL_SCANCODE_C, "C");
	keys[SDL_SCANCODE_D] = new KeyboardKey(SDL_SCANCODE_D, "D");
	keys[SDL_SCANCODE_E] = new KeyboardKey(SDL_SCANCODE_E, "E");
	keys[SDL_SCANCODE_F] = new KeyboardKey(SDL_SCANCODE_F, "F");
	keys[SDL_SCANCODE_G] = new KeyboardKey(SDL_SCANCODE_G, "G");
	keys[SDL_SCANCODE_H] = new KeyboardKey(SDL_SCANCODE_H, "H");
	keys[SDL_SCANCODE_I] = new KeyboardKey(SDL_SCANCODE_I, "I");
	keys[SDL_SCANCODE_J] = new KeyboardKey(SDL_SCANCODE_J, "J");
	keys[SDL_SCANCODE_K] = new KeyboardKey(SDL_SCANCODE_K, "K");
	keys[SDL_SCANCODE_L] = new KeyboardKey(SDL_SCANCODE_L, "L");
	keys[SDL_SCANCODE_M] = new KeyboardKey(SDL_SCANCODE_M, "M");
	keys[SDL_SCANCODE_N] = new KeyboardKey(SDL_SCANCODE_N, "N");
	keys[SDL_SCANCODE_O] = new KeyboardKey(SDL_SCANCODE_O, "O");
	keys[SDL_SCANCODE_P] = new KeyboardKey(SDL_SCANCODE_P, "P");
	keys[SDL_SCANCODE_Q] = new KeyboardKey(SDL_SCANCODE_Q, "Q");
	keys[SDL_SCANCODE_R] = new KeyboardKey(SDL_SCANCODE_R, "R");
	keys[SDL_SCANCODE_S] = new KeyboardKey(SDL_SCANCODE_S, "S");
	keys[SDL_SCANCODE_T] = new KeyboardKey(SDL_SCANCODE_T, "T");
	keys[SDL_SCANCODE_U] = new KeyboardKey(SDL_SCANCODE_U, "U");
	keys[SDL_SCANCODE_V] = new KeyboardKey(SDL_SCANCODE_V, "V");
	keys[SDL_SCANCODE_W] = new KeyboardKey(SDL_SCANCODE_W, "W");
	keys[SDL_SCANCODE_X] = new KeyboardKey(SDL_SCANCODE_X, "X");
	keys[SDL_SCANCODE_Y] = new KeyboardKey(SDL_SCANCODE_Y, "Y");
	keys[SDL_SCANCODE_Z] = new KeyboardKey(SDL_SCANCODE_Z, "Z");

	keys[SDL_SCANCODE_1] = new KeyboardKey(SDL_SCANCODE_1, "1");
	keys[SDL_SCANCODE_2] = new KeyboardKey(SDL_SCANCODE_2, "2");
	keys[SDL_SCANCODE_3] = new KeyboardKey(SDL_SCANCODE_3, "3");
	keys[SDL_SCANCODE_4] = new KeyboardKey(SDL_SCANCODE_4, "4");
	keys[SDL_SCANCODE_5] = new KeyboardKey(SDL_SCANCODE_5, "5");
	keys[SDL_SCANCODE_6] = new KeyboardKey(SDL_SCANCODE_6, "6");
	keys[SDL_SCANCODE_7] = new KeyboardKey(SDL_SCANCODE_7, "7");
	keys[SDL_SCANCODE_8] = new KeyboardKey(SDL_SCANCODE_8, "8");
	keys[SDL_SCANCODE_9] = new KeyboardKey(SDL_SCANCODE_9, "9");
	keys[SDL_SCANCODE_0] = new KeyboardKey(SDL_SCANCODE_0, "0");

	keys[SDL_SCANCODE_RETURN]		= new KeyboardKey(SDL_SCANCODE_RETURN, "Enter");
	keys[SDL_SCANCODE_ESCAPE]		= new KeyboardKey(SDL_SCANCODE_ESCAPE, "Escape");
	keys[SDL_SCANCODE_BACKSPACE]	= new KeyboardKey(SDL_SCANCODE_BACKSPACE, "Backspace");
	keys[SDL_SCANCODE_TAB]			= new KeyboardKey(SDL_SCANCODE_TAB, "Tab");
	keys[SDL_SCANCODE_SPACE]		= new KeyboardKey(SDL_SCANCODE_SPACE, "Space");
	keys[SDL_SCANCODE_MINUS]		= new KeyboardKey(SDL_SCANCODE_MINUS, "-");
	keys[SDL_SCANCODE_EQUALS]		= new KeyboardKey(SDL_SCANCODE_EQUALS, "=");
	keys[SDL_SCANCODE_LEFTBRACKET]	= new KeyboardKey(SDL_SCANCODE_LEFTBRACKET, "[");
	keys[SDL_SCANCODE_RIGHTBRACKET] = new KeyboardKey(SDL_SCANCODE_RIGHTBRACKET, "]");
	keys[SDL_SCANCODE_BACKSLASH]	= new KeyboardKey(SDL_SCANCODE_BACKSLASH, "\\");
	keys[SDL_SCANCODE_NONUSHASH]	= new KeyboardKey(SDL_SCANCODE_NONUSHASH, "");
	keys[SDL_SCANCODE_SEMICOLON]	= new KeyboardKey(SDL_SCANCODE_SEMICOLON, ";");
	keys[SDL_SCANCODE_APOSTROPHE]	= new KeyboardKey(SDL_SCANCODE_APOSTROPHE, "'");
	keys[SDL_SCANCODE_GRAVE]		= new KeyboardKey(SDL_SCANCODE_GRAVE, "`");
	keys[SDL_SCANCODE_COMMA]		= new KeyboardKey(SDL_SCANCODE_COMMA, ",");
	keys[SDL_SCANCODE_PERIOD]		= new KeyboardKey(SDL_SCANCODE_PERIOD, ".");
	keys[SDL_SCANCODE_SLASH]		= new KeyboardKey(SDL_SCANCODE_SLASH, "/");
	keys[SDL_SCANCODE_CAPSLOCK]		= new KeyboardKey(SDL_SCANCODE_CAPSLOCK, "Capslock");

	keys[SDL_SCANCODE_F1] = new KeyboardKey(SDL_SCANCODE_F1, "F1");
	keys[SDL_SCANCODE_F2] = new KeyboardKey(SDL_SCANCODE_F2, "F2");
	keys[SDL_SCANCODE_F3] = new KeyboardKey(SDL_SCANCODE_F3, "F3");
	keys[SDL_SCANCODE_F4] = new KeyboardKey(SDL_SCANCODE_F4, "F4");
	keys[SDL_SCANCODE_F5] = new KeyboardKey(SDL_SCANCODE_F5, "F5");
	keys[SDL_SCANCODE_F6] = new KeyboardKey(SDL_SCANCODE_F6, "F6");
	keys[SDL_SCANCODE_F7] = new KeyboardKey(SDL_SCANCODE_F7, "F7");
	keys[SDL_SCANCODE_F8] = new KeyboardKey(SDL_SCANCODE_F8, "F8");
	keys[SDL_SCANCODE_F9] = new KeyboardKey(SDL_SCANCODE_F9, "F9");
	keys[SDL_SCANCODE_F10] = new KeyboardKey(SDL_SCANCODE_F10, "F10");
	keys[SDL_SCANCODE_F11] = new KeyboardKey(SDL_SCANCODE_F11, "F11");
	keys[SDL_SCANCODE_F12] = new KeyboardKey(SDL_SCANCODE_F12, "F12");

	keys[SDL_SCANCODE_PRINTSCREEN] = new KeyboardKey(SDL_SCANCODE_PRINTSCREEN, "F12");
	keys[SDL_SCANCODE_SCROLLLOCK] = new KeyboardKey(SDL_SCANCODE_SCROLLLOCK, "F12");
	keys[SDL_SCANCODE_PAUSE] = new KeyboardKey(SDL_SCANCODE_PAUSE, "F12");
	keys[SDL_SCANCODE_INSERT] = new KeyboardKey(SDL_SCANCODE_INSERT, "F12");
	keys[SDL_SCANCODE_HOME] = new KeyboardKey(SDL_SCANCODE_HOME, "F12");
	keys[SDL_SCANCODE_PAGEUP] = new KeyboardKey(SDL_SCANCODE_PAGEUP, "F12");
	keys[SDL_SCANCODE_RIGHT] = new KeyboardKey(SDL_SCANCODE_RIGHT, "F12");
	keys[SDL_SCANCODE_LEFT] = new KeyboardKey(SDL_SCANCODE_LEFT, "F12");
	keys[SDL_SCANCODE_DOWN] = new KeyboardKey(SDL_SCANCODE_DOWN, "F12");
	keys[SDL_SCANCODE_UP] = new KeyboardKey(SDL_SCANCODE_UP, "F12");
	keys[SDL_SCANCODE_NUMLOCKCLEAR] = new KeyboardKey(SDL_SCANCODE_NUMLOCKCLEAR, "F12");
	
	keys[SDL_SCANCODE_KP_DIVIDE] = new KeyboardKey(SDL_SCANCODE_KP_DIVIDE, "F12");
	keys[SDL_SCANCODE_KP_MULTIPLY] = new KeyboardKey(SDL_SCANCODE_KP_MULTIPLY, "F12");
	keys[SDL_SCANCODE_KP_MINUS] = new KeyboardKey(SDL_SCANCODE_KP_MINUS, "F12");
	keys[SDL_SCANCODE_KP_PLUS] = new KeyboardKey(SDL_SCANCODE_KP_PLUS, "F12");
	keys[SDL_SCANCODE_KP_ENTER] = new KeyboardKey(SDL_SCANCODE_KP_ENTER, "F12");
	keys[SDL_SCANCODE_KP_1] = new KeyboardKey(SDL_SCANCODE_KP_1, "1");
	keys[SDL_SCANCODE_KP_2] = new KeyboardKey(SDL_SCANCODE_KP_2, "2");
	keys[SDL_SCANCODE_KP_3] = new KeyboardKey(SDL_SCANCODE_KP_3, "3");
	keys[SDL_SCANCODE_KP_4] = new KeyboardKey(SDL_SCANCODE_KP_4, "4");
	keys[SDL_SCANCODE_KP_5] = new KeyboardKey(SDL_SCANCODE_KP_5, "5");
	keys[SDL_SCANCODE_KP_6] = new KeyboardKey(SDL_SCANCODE_KP_6, "6");
	keys[SDL_SCANCODE_KP_7] = new KeyboardKey(SDL_SCANCODE_KP_7, "7");
	keys[SDL_SCANCODE_KP_8] = new KeyboardKey(SDL_SCANCODE_KP_8, "8");
	keys[SDL_SCANCODE_KP_9] = new KeyboardKey(SDL_SCANCODE_KP_9, "9");
	keys[SDL_SCANCODE_KP_0] = new KeyboardKey(SDL_SCANCODE_KP_0, "0");

	keys[SDL_SCANCODE_MOUSE_LEFT]			= new KeyboardKey(SDL_SCANCODE_MOUSE_LEFT, "Mouse Left");
	keys[SDL_SCANCODE_MOUSE_MIDDLE]			= new KeyboardKey(SDL_SCANCODE_MOUSE_MIDDLE, "Mouse Middle");
	keys[SDL_SCANCODE_MOUSE_RIGHT]			= new KeyboardKey(SDL_SCANCODE_MOUSE_RIGHT, "Mouse Right");
	keys[SDL_SCANCODE_MOUSE_FORWARD]		= new KeyboardKey(SDL_SCANCODE_MOUSE_FORWARD, "Mouse Forward");
	keys[SDL_SCANCODE_MOUSE_BACK]			= new KeyboardKey(SDL_SCANCODE_MOUSE_BACK, "Mouse Back");
	keys[SDL_SCANCODE_MOUSE_SCROLL_UP]		= new KeyboardKey(SDL_SCANCODE_MOUSE_SCROLL_UP, "Scroll Up");
	keys[SDL_SCANCODE_MOUSE_SCROLL_DOWN]	= new KeyboardKey(SDL_SCANCODE_MOUSE_SCROLL_DOWN, "Scroll Down");

    //gz::print_value("keycount=",sf::Keyboard::KeyCount);


    //kbKeys[40] = kbKeys(7,"B");
}

void GameData::updateKeys()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < keys.size() - 18; ++i)
	{
		KeyboardKey* key = keys[i];
		if (key != NULL)
		{
			key->updateKey(keystate[key->m_key]);
		}
	}

	keys[SDL_SCANCODE_MOUSE_LEFT]->updateKey(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
	keys[SDL_SCANCODE_MOUSE_MIDDLE]->updateKey(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	keys[SDL_SCANCODE_MOUSE_RIGHT]->updateKey(SDL_GetMouseState(NULL, NULL) &SDL_BUTTON(SDL_BUTTON_RIGHT));
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
	
	int pixel_x = surface->w / 2 + (x * (WORLD_SCALE * zoom));
	int pixel_y = surface->h / 2 - (y * (WORLD_SCALE * zoom));

    return Vector2(pixel_x,pixel_y);
}


