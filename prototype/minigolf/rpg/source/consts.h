#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

#include <string>
#include "Box2D/Box2D.h"

using namespace std;

// system::settings
static const string    SETTINGS_FILENAME = "data/config.ini";
static const unsigned       SETTINGS_DEFAULT_FPSLIMIT = 0;
static const bool           SETTINGS_DEFAULT_VSYNC = false;
static const bool           SETTINGS_DEFAULT_FULLSCREEN = false;
static const unsigned       SETTINGS_DEFAULT_WIDTH = 800;
static const unsigned       SETTINGS_DEFAULT_HEIGHT = 600;

// level
static const string			LEVEL_PATH = "data/levels/level_";

// GUI
static const unsigned       GUI_FONT_DEFAULT_SIZE = 12;
static const std::string    GUI_FONT_DEFAULT_PATH = "media/fonts/puristal.otf";
//static const sf::Color      GUI_FONT_DEFAULT_COLOUR = sf::Color(0,0,0);

// physics
static const int            ONE_SECOND_INT = 1000;
static const float          ONE_SECOND_FLOAT = 1000.0f;
static const float          WORLD_SCALE = 50.f;
static const b2Vec2         GRAVITY(0.f,0.f);
static const double         PI       = 3.141592653589793;
static const double         DEGTORAD = PI / 180;
static const double         RADTODEG = 180 / PI;

static const double         MAX_TIME_STEP = 1.f / 30.f;
static const double         MIN_TIME_STEP = 1.f / 2048.f;
static const int            MAX_SUB_STEPS = 5;

static const int            MAX_VELOCITY_ITERATIONS = 8;
static const int            MAX_POSITION_ITERATIONS = 3;

static const int            KEY_MOUSE_LEFT = 101;
static const int            KEY_MOUSE_RIGHT = 102;
static const int            KEY_MOUSE_MIDDLE = 103;
static const int            KEY_MOUSE_BUTTON4 = 104;
static const int            KEY_MOUSE_BUTTON5 = 105;
static const int            KEY_MOUSE_SCROLL_UP = 106;
static const int            KEY_MOUSE_SCROLL_DOWN = 107;

#endif // CONSTS_H_INCLUDED
