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

		SDL_atomic_t	inuse;
		AssetManager*	assets = nullptr;
		Camera*			camera = nullptr;

		bool			running = true;
		SDL_Window*		window = nullptr;
		SDL_Surface*	surface = nullptr;
		SDL_Renderer*	renderer = nullptr;
		Settings*		settings = nullptr;
		RunState		gamestate = STATE_GAME;

		float			zoom = 1.0;
		double			m_timeDelta = 0;

		Object* player = nullptr;
		bool player_moved = true;

    public:
		void updateKeys();
		vector<KeyboardKey*>	keys;
		Vector2 toPixels(float x, float y);
};


extern GameData gdata;
#endif // GAMEDATA_H
