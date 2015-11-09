#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

enum Align
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    MIDDLE,
};


enum ObjectType
{
    NONE,
    PLAYER,
    HOLE,
    WALL,
    PARTICLE,
    GHOST_PLAYER,
};

enum SwitchType
{
    TOGGLE      = 0,
    TIMED       = 1,
    CONTINUOUS  = 2,
    SINGLE      = 3,
};

enum SwitchBits
{
    SW_MOV = 0x0001,
    SW_ROT = 0x0002,
    SW_ENB = 0x0004,
};

enum CollisionGroups
{
    CF_NONE                = 0x0000,
    CF_PHYSICAL_OBJECT     = 0x0001,
    CF_SENSOR              = 0x0002,
    CF_PLAYER              = 0x0004,
    CF_WALL                = 0x0008,
	CF_GROUND			   = 0x0010,
	CF_HOLE                = 0x0020,
	CF_SWITCH              = 0x0040,
	CF_PARTICLE            = 0x0080,
	CF_EPARTICLE           = 0x0100,
    CF_ALL                 = 0xFFFF,
};

enum RunState
{
    STATE_MENU     = 0,
    STATE_GAME     = 1,
};

enum ExtraKeys
{
    KEY_MOUSE_LEFT          = 101,
    KEY_MOUSE_RIGHT         = 102,
    KEY_MOUSE_MIDDLE        = 103,
    KEY_MOUSE_BUTTON_4      = 104,
    KEY_MOUSE_BUTTON_5      = 105,
    KEY_MOUSE_SCROLL_UP     = 106,
    KEY_MOUSE_SCROLL_DOWN   = 107,
};

enum MenuState
{
    MENU_MAIN               = 201,
    MENU_AWARDS             = 202,
    MENU_OPTIONS            = 203,
    MENU_LEVELS             = 204,
};

#endif // ENUMS_H_INCLUDED
