#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "general.h"

class Camera;
class Settings;
class AssetManager;
class Object;

class GameData
{
    public:
		GameData();
		virtual ~GameData(){}

    public: // variables
        bool			running = true;
		RunState		gamestate = STATE_MENU;

		AssetManager*	    assets = nullptr;
		sf::RenderWindow*   window = nullptr;
		Settings*		    settings = nullptr;
		Camera*			    camera = nullptr;
		b2World*		    world = nullptr;

		float			zoom = 1.0;
		double			m_timeDelta = 0;
		Vector2         mouse;

		//Object* player = nullptr;

    public:
		void updateKeys();
		vector<KeyboardKey>	keys;
		Vector2 toPixels(float x, float y);
};


extern GameData gdata;
#endif // GAMEDATA_H
