#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

enum SDLScancodeMouse
{
	SDL_SCANCODE_MOUSE_LEFT			= 290,
	SDL_SCANCODE_MOUSE_MIDDLE		= 291,
	SDL_SCANCODE_MOUSE_RIGHT		= 292,
	SDL_SCANCODE_MOUSE_BACK			= 293,
	SDL_SCANCODE_MOUSE_FORWARD		= 294,
	SDL_SCANCODE_MOUSE_SCROLL_UP	= 295,
	SDL_SCANCODE_MOUSE_SCROLL_DOWN	= 296,
};

enum CollisionGroups
{
    CF_PHYSICAL_OBJECT     = 0x0001,
    CF_SENSOR              = 0x0002,
    CF_PLAYER              = 0x0004,
    CF_NPC                 = 0x0008,
	CF_GROUND			   = 0x0010,
	CF_PIPE				   = 0x0020,
	CF_HOLE				   = 0x0040,
    CF_ALL                 = 0xFFFF,
};

enum ObjectType
{
	NONE,
	PIPE,
	HOLE,
	PLAYER,
};

enum Align
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    MIDDLE,
};

enum RunState
{
    STATE_MENU     = 0,
    STATE_GAME     = 1,
};

enum guiState
{
    GUI_STATE_IDLE      = 0,
    GUI_STATE_SELECTED  = 1,
    GUI_STATE_HOVER     = 2,
    GUI_STATE_ACTIVE    = 4,
    GUI_STATE_CHECKED   = 8,
    GUI_STATE_UNCHECKED = 16,
};

enum guiEventType
{
    GET_ACTIVATED       = 0,
    GET_GOT_FOCUS       = 1,
    GET_LOST_FOCUS      = 2,
};

enum JoystickButtons
{
    JOYSTICK_BUTTON_A               = 0,
    JOYSTICK_BUTTON_B               = 1,
    JOYSTICK_BUTTON_X               = 2,
    JOYSTICK_BUTTON_Y               = 3,
    JOYSTICK_BUTTON_LB              = 4,
    JOYSTICK_BUTTON_RB              = 5,
    JOYSTICK_BUTTON_BACK            = 6,
    JOYSTICK_BUTTON_START           = 7,
    JOYSTICK_BUTTON_LEFT_JOYSTICK   = 8,
    JOYSTICK_BUTTON_RIGHT_JOYSTICK  = 9,
};

#endif // ENUMS_H_INCLUDED
