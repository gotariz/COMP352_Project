#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "general.h"
#include "video/Camera.h"

//class Camera;
class Settings;
class AssetManager;
class Object;
class PhysicsFactory;
class AudioManager;

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
		PhysicsFactory*     factory = nullptr;
		AudioManager*       audio = nullptr;

		float			zoom = 1.0;
		double			m_timeDelta = 0;
		Vector2         mouse;
		Vector2         mouse_raw;

		sf::View*       view = nullptr;
		int             level = 1;
		bool            reload = false;
		float           countdown = 0;

		bool            draw_debug = false;
		bool            draw_grid = false;
		//bool            has_focus = true;

        Vector2         t_p1;
        Vector2         t_p2;
        bool            play_slidein    = false;
        bool            play_slideout   = false;
        float           slideout_time   = 0;

    public:

		void updateKeys();
		vector<KeyboardKey>	keys;
		Vector2 toPixels(float x, float y);
		Vector2 toPixels(Vector2 p);
		Vector2 toPixels(b2Vec2 p);

		Vector2 toScreenPixels(float x, float y);
		Vector2 toScreenPixels(Vector2 p);
		Vector2 toScreenPixels(b2Vec2 p);
};


extern GameData gdata;
#endif // GAMEDATA_H
