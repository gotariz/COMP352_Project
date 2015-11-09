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
class MusicHandle;
class AchievementBar;

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


        bool angle_snap = 1;
        MusicHandle*    bg_music = nullptr;

		bool            draw_debug = false;
		bool            draw_grid = false;

        bool            draw_last = true;
		bool            first_shot = true;
		bool            last_angle = 0;
		Vector2         p1;
		Vector2         p2;
		bool            show_progress = false;

		bool            show_help = false;
		bool            random_colors = false;

		int             bounce_counter = 0;

		vector<AchievementBar*> achieves;

        bool replay_level = false;
		vector<BallShotData>    shotData;

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
